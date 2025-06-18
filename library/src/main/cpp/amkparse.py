# Copyright (c) 2006-2024 LOVE Development Team
#
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#

import io
import json
import os
import re
import sys


P_COMMENTS = re.compile(r"(?<!\\)#.+")
P_CONTINUATION = re.compile(r"\s*\\\r?\n\s*")
P_EMPTY_LINE = re.compile(r"\s*[\r?\n]+\s*")
P_VAR_ASSIGN = re.compile(r"([a-zA-Z_]\w*)\s*:?:?=\"?\s*(.*)\"?")
P_MULTI_WHITESPACE = re.compile(r"\s+")
P_CLEAN_VARS = re.compile(r"include\s*\$[\(\{]CLEAR_VARS[\)\}]\s*", re.MULTILINE)
P_VARIABLE_REF = re.compile(r"\$[\(\{]([a-zA-Z_]\w*)[\)\}]")

P_BUILD_TYPES = {
    "executable": re.compile(r"include\s*\$[\(\{]BUILD_EXECUTABLE[\)\}]\s*", re.MULTILINE),
    "shared": re.compile(r"include\s*\$[\(\{]BUILD_SHARED_LIBRARY[\)\}]\s*", re.MULTILINE),
    "static": re.compile(r"include\s*\$[\(\{]BUILD_STATIC_LIBRARY[\)\}]\s*", re.MULTILINE),
    "prebuilt_shared": re.compile(r"include\s*\$[\(\{]PREBUILT_SHARED_LIBRARY[\)\}]\s*", re.MULTILINE),
    "prebuilt_static": re.compile(r"include\s*\$[\(\{]PREBUILT_STATIC_LIBRARY[\)\}]\s*", re.MULTILINE),
}

substitute_love_with_luajit = True


def transform_makefile(mk: str):
    # Remove comments
    mk = re.sub(P_COMMENTS, "", mk)
    # Remove multiline declaration
    mk = re.sub(P_CONTINUATION, " ", mk)
    # Remove multiple newlines
    mk = re.sub(P_EMPTY_LINE, "\n", mk)
    mk = re.sub(P_EMPTY_LINE, "\n", mk)
    # Simplify assignment
    mk = re.sub(P_VAR_ASSIGN, r"\1=\2", mk)
    return mk


def list_if_needed(data):
    if isinstance(data, str):
        return [data]
    return data


def str_if_needed(data):
    if isinstance(data, list):
        return " ".join(data)
    return data


def expand_value(value: str, variables: dict[str, str]):
    def do_replace(x: re.Match[str]):
        v = x.group(1)
        return str_if_needed(variables.get(v, f"$({v})"))

    return re.sub(P_VARIABLE_REF, do_replace, value)


def extract_variables(mk: str, variables: dict[str, str] = None):
    result = {}
    for match in re.finditer(P_VAR_ASSIGN, mk):
        value = match.group(2).strip()
        # Try convert to boolean
        if value == "true" or value == "false":
            value = value == "true"
        # Is it array of strings?
        elif value.find(" ") >= 0:
            if variables:
                # Expand first
                value = expand_value(value, variables)
            value = re.sub(P_MULTI_WHITESPACE, " ", value).split(" ")
        else:
            try:
                # Try int conversion
                value = int(value)
            except ValueError:
                try:
                    # Try float conversion
                    value = float(value)
                except ValueError:
                    # Fallback default (str)
                    if variables:
                        value = expand_value(value, variables)
        result[match.group(1)] = value
    return result


def separate_makefiles(mk: str):
    # Normalize "include $(CLEAR_VARS)"
    result = re.sub(P_CLEAN_VARS, "include $(CLEAN_VARS)", mk).split("include $(CLEAN_VARS)")
    # Transform makefile
    result = map(transform_makefile, result)
    # Remove "LOCAL_PATH"
    def test_filt(x):
        return x.find("LOCAL_PATH=") == -1

    result = filter(test_filt, result)
    return list(result)


def extract_variables_with_expand(mk: str, target_vars: dict[str, str]):
    variables = extract_variables(mk, target_vars)
    variables = extract_variables(mk, variables | target_vars)
    return variables


def determine_build_type(mk: str):
    for name, pattern in P_BUILD_TYPES.items():
        if re.search(pattern, mk):
            return name
    return "unknown"


class CFlagsData:
    def __init__(self, cflags: str):
        # Variable setup
        self.standard = None
        self.include_paths = []
        self.features = set()
        self.defines = set()
        self.other = []
        # Parse
        for flag in cflags.split():
            if flag.startswith("-std="):
                # std
                value = flag[5:].replace("gnu++", "c++")
                if value == "c99":
                    self.standard = 99
                elif value == "c++11" or value == "c++0x" or value == "c11":
                    self.standard = 11
                elif value == "c++14":
                    self.standard = 14
                elif value == "c++17" or value == "c17":
                    self.standard = 17
                elif value == "c++2a" or value == "c++20":
                    self.standard = 20
                else:
                    print(f"Unknown -std: {value}", file=sys.stderr)
            elif flag.startswith("-I"):
                # Include paths
                self.include_paths.append(flag[2:])
            elif flag.startswith("-f"):
                # Features
                self.features.add(flag[2:])
            elif flag.startswith("-D"):
                # Defines
                self.defines.add(flag[2:])
            else:
                self.other.append(flag)

    @property
    def unknowns(self):
        return " ".join(self.others)


class LDFlagsData:
    def __init__(self, ldflags: str):
        # Variable setup
        self.libraries = set()
        self.library_paths = []
        self.other = []
        # Parse
        for flag in ldflags.split():
            if flag.startswith("-fuse-ld="):
                # linker, ignore
                pass
            elif flag.startswith("-l"):
                # Native, built-in libraries
                self.libraries.add(flag[2:])
            elif flag.startswith("-L"):
                # Library paths
                self.library_paths.append(flag[2:])
            else:
                self.other.append(flag)

    @property
    def unknowns(self):
        return " ".join(self.others)


def filter_libraries(name: str):
    if len(name) < 2:
        return name
    if name[0] == "-":
        if name[1] == "l":
            return name[2:]
    else:
        if name.startswith("lib"):
            return name[3:]
        return name
    return ""


def get_default_output_file(name: str):
    return name if name.startswith("lib") else ("lib" + name)


class SerializedMakefile:
    def __init__(self, mk: str, compatsubst: bool = True):
        variables = extract_variables_with_expand(mk, target_vars)
        build_type = determine_build_type(mk)
        # Essential
        self.name = variables["LOCAL_MODULE"]
        if self.name.startswith("lib"):
            self.name = self.name[3:]
        self.output = variables.get("LOCAL_MODULE_FILENAME", get_default_output_file(self.name))
        self.type = build_type
        self.sources = list_if_needed(variables["LOCAL_SRC_FILES"])
        self.include = list_if_needed(variables.get("LOCAL_C_INCLUDES", []))
        self.export_include = list_if_needed(variables.get("LOCAL_EXPORT_C_INCLUDES", []))
        self.allow_undefined = str_if_needed(variables.get("LOCAL_ALLOW_UNDEFINED_SYMBOLS", "")).lower() == "true"
        self.force_arm_code = str_if_needed(variables.get("LOCAL_ARM_MODE", "")) == "arm"
        # CFlags
        cflags = CFlagsData(str_if_needed(variables.get("LOCAL_CFLAGS", "")))
        export_cflags = CFlagsData(str_if_needed(variables.get("LOCAL_EXPORT_CFLAGS", "")))
        cppflags = CFlagsData(str_if_needed(variables.get("LOCAL_CPPFLAGS", "")))
        export_cppflags = CFlagsData(str_if_needed(variables.get("LOCAL_EXPORT_CPPFLAGS", "")))
        self.include.extend(cflags.include_paths)
        self.include.extend(cppflags.include_paths)
        self.export_include.extend(export_cflags.include_paths)
        self.export_include.extend(export_cppflags.include_paths)
        # C flags
        self.c_standard = cflags.standard
        self.c_compile_features = list(cflags.features)
        self.c_compile_flags = cflags.other
        self.export_c_standard = export_cflags.standard
        self.export_c_compile_features = list(export_cflags.features)
        self.export_c_compile_flags = export_cflags.other
        # C++ flags
        self.cpp_standard = cppflags.standard
        self.cpp_compile_features = list(cppflags.features)
        self.cpp_compile_flags = cppflags.other
        self.export_cpp_standard = export_cppflags.standard
        self.export_cpp_compile_features = list(export_cppflags.features)
        self.export_cpp_compile_flags = export_cppflags.other
        # Linker flags/libraries
        link_libraries = set()
        link_libraries.update(
            filter_libraries(name) for name in list_if_needed(variables.get("LOCAL_SHARED_LIBRARIES", []))
        )
        link_libraries.update(
            filter_libraries(name) for name in list_if_needed(variables.get("LOCAL_STATIC_LIBRARIES", []))
        )
        self.link_library_path = []
        self.link_library_options = []
        if build_type.find("static") == -1:
            ldflags = LDFlagsData(str_if_needed(variables.get("LOCAL_LDFLAGS", "")))
            ldlibs = list_if_needed(variables.get("LOCAL_LDLIBS", []))
            link_libraries.update(filter_libraries(name) for name in ldlibs)
            link_libraries.update(filter_libraries(name) for name in ldflags.libraries)
            self.link_library_path.extend(ldflags.library_paths)
            self.link_library_options.extend(ldflags.other)
        self.link_libraries = list(filter(None, link_libraries))
        export_ldflags = LDFlagsData(str_if_needed(variables.get("LOCAL_EXPORT_LDFLAGS", "")))
        export_link_libraries = set()
        export_link_libraries.update(
            filter_libraries(name) for name in list_if_needed(variables.get("LOCAL_LDLIBS", []))
        )
        export_link_libraries.update(filter_libraries(name) for name in export_ldflags.libraries)
        self.export_link_library_path = export_ldflags.library_paths
        self.export_link_library_options = export_ldflags.other
        self.export_link_libraries = list(filter(None, export_link_libraries))
        if compatsubst:
            self.link_libraries = list(map(lambda x: "luajit" if x == "love" else x, self.link_libraries))
            self.export_link_libraries = list(map(lambda x: "luajit" if x == "love" else x, self.export_link_libraries))

    def __iter__(self):
        yield "name", self.name,
        yield "output", self.output,
        yield "type", self.type,
        yield "allowUndefined", self.allow_undefined
        yield "forceARMCode", self.force_arm_code
        yield "sources", self.sources
        yield "include", self.include
        yield "exportInclude", self.export_include
        yield "cStandard", self.c_standard
        yield "cCompileFeatures", self.c_compile_features
        yield "cCompileFlags", self.c_compile_flags
        yield "cppStandard", self.cpp_standard
        yield "cppCompileFeatures", self.cpp_compile_features
        yield "cppCompileFlags", self.cpp_compile_flags
        yield "exportCStandard", self.export_c_standard
        yield "exportCCompileFeatures", self.export_c_compile_features
        yield "exportCCompileFlags", self.export_c_compile_flags
        yield "exportCppStandard", self.export_cpp_standard
        yield "exportCppCompileFeatures", self.export_cpp_compile_features
        yield "exportCppCompileFlags", self.export_cpp_compile_flags
        yield "linkLibraries", self.link_libraries
        yield "linkLibraryPath", self.link_library_path
        yield "linkLibraryOptions", self.link_library_options
        yield "exportLinkLibraries", self.export_link_libraries
        yield "exportLinkLibraryPath", self.export_link_library_path
        yield "exportLinkLibraryOptions", self.export_link_library_options


def convert_to_serialized(mk: list[str], target_vars: dict[str, str]):
    result = []  # type: list[SerializedMakefile]
    for mks in mk:
        result.append(SerializedMakefile(mks, substitute_love_with_luajit))
    return result


def convert_to_json(mk: list[str], target_vars: dict[str, str]):
    return json.dumps([dict(x) for x in convert_to_serialized(mk, target_vars)])


def write_cmake(stream: io.StringIO, funcname: str, target: str, kind: str = None, props: list[str] = None):
    stream.write(funcname)
    stream.write("(")
    stream.write(target)
    if kind:
        stream.write(" ")
        stream.write(kind)
    if props:
        stream.write("\n")
        for prop in props:
            stream.write("\t")
            stream.write(prop)
            stream.write("\n")
    stream.write(")\n")


def convert_to_cmake(mk: list[str], target_vars: dict[str, str], project: str):
    serialized_mk = convert_to_serialized(mk, target_vars)
    result = io.StringIO()
    result.write("# Generated by amkparse.py\n")
    result.write("# Modify if needed then remove this comment.\n")
    result.write("cmake_minimum_required(VERSION 3.22)\n\n")
    result.write(f"project({project} LANGUAGES C CXX)\n\n")
    for s in serialized_mk:
        result.write(f"#\n# {s.name}\n#\n")
        if s.type.startswith("prebuilt"):
            # Prebuilt needs either .so or .a
            kind = "SHARED" if s.type.find("shared") != -1 else "STATIC"
            write_cmake(result, "add_library", s.name, f"IMPORTED {kind}")
            write_cmake(result, "set_target_properties", s.name, "PROPERTIES", [f'IMPORTED_LOCATION "{s.sources[0]}"'])
            if len(s.export_include) > 0:
                write_cmake(result, "target_include_directories", s.name, "INTERFACE", s.export_include)
        else:
            # add_library/add_executable
            if s.type == "executable":
                write_cmake(result, "add_executable", s.name, None, s.sources)
            else:
                kind = "SHARED" if s.type.find("shared") != -1 else "STATIC"
                write_cmake(result, "add_library", s.name, kind, s.sources)
            # set_target_properties
            c_standard = s.export_c_standard or s.c_standard
            cpp_standard = s.export_cpp_standard or s.cpp_standard
            target_props = [f"OUTPUT_NAME {s.output}", 'PREFIX ""']
            if c_standard:
                target_props.append(f"C_STANDARD {c_standard}")
            if cpp_standard:
                target_props.append(f"CXX_STANDARD {cpp_standard}")
            write_cmake(result, "set_target_properties", s.name, "PROPERTIES", target_props)
            # target_include_directories PRIVATE
            if len(s.include) > 0:
                write_cmake(result, "target_include_directories", s.name, "PRIVATE", s.include)
            # target_include_directories PUBLIC
            if len(s.export_include) > 0:
                write_cmake(result, "target_include_directories", s.name, "PUBLIC", s.export_include)
            # target_link_directories PRIVATE
            if len(s.link_library_path) > 0:
                write_cmake(result, "target_link_directories", s.name, "PRIVATE", s.link_library_path)
            # target_link_directories PUBLIC
            if len(s.export_link_library_path) > 0:
                write_cmake(result, "target_link_directories", s.name, "PUBLIC", s.export_link_library_path)
            # target_link_libraries
            link_libraries = None
            export_link_libraries = None
            if s.type.find("static") != -1:
                # Merge export and non-export
                export_link_libraries = set()
                export_link_libraries.update(s.link_libraries)
                export_link_libraries.update(s.export_link_libraries)
            else:
                link_libraries = s.link_libraries
                export_link_libraries = s.export_link_libraries
            if link_libraries:
                write_cmake(result, "target_link_libraries", s.name, "PRIVATE", link_libraries)
            if export_link_libraries:
                write_cmake(result, "target_link_libraries", s.name, "PUBLIC", export_link_libraries)
            if len(s.c_compile_flags) > 0:
                print("# TODO: compile flags:", *s.c_compile_flags, file=result)
            if len(s.c_compile_features) > 0:
                print("# TODO: compile features:", *s.c_compile_features, file=result)
            if len(s.cpp_compile_flags) > 0:
                print("# TODO: compile flags cpp:", *s.cpp_compile_flags, file=result)
            if len(s.cpp_compile_features) > 0:
                print("# TODO: compile features cpp:", *s.cpp_compile_features, file=result)
            if len(s.export_c_compile_flags) > 0:
                print("# TODO: export compile flags:", *s.export_c_compile_flags, file=result)
            if len(s.export_c_compile_features) > 0:
                print("# TODO: export compile features:", *s.export_c_compile_features, file=result)
            if len(s.export_c_compile_flags) > 0:
                print("# TODO: export compile flags cpp:", *s.export_c_compile_flags, file=result)
            if len(s.export_c_compile_features) > 0:
                print("# TODO: export compile features cpp:", *s.export_c_compile_features, file=result)
            if len(s.link_library_options) > 0:
                print("# TODO: link options:", *s.link_library_options, file=result)
            if len(s.export_link_library_options) > 0:
                print("# TODO: export link options:", *s.export_link_library_options, file=result)
    return result.getvalue()


def create_target_vars(path: str, arch: str, api: str):
    if arch == "cmake":
        return {
            "LOCAL_PATH": "${CMAKE_CURRENT_SOURCE_DIR}",
            "TARGET_ARCH": "${CMAKE_ANDROID_ARCH}",
            "TARGET_ARCH_ABI": "${CMAKE_ANDROID_ARCH_ABI}",
            "TARGET_PLATFORM": "android-${CMAKE_SYSTEM_NAME}",
            "TARGET_ABI": "android-${CMAKE_SYSTEM_NAME}-${CMAKE_ANDROID_ARCH_ABI}",
        }
    if arch == "arm64" or arch == "arm64-v8a":
        arch_pure = "arm64"
        arch_abi = "arm64-v8a"
    elif arch == "armeabi-v7a" or arch == "arm":
        arch_pure = "arm"
        arch_abi = "armeabi-v7a"
    else:
        arch_pure = arch
        arch_abi = arch
    return {
        "LOCAL_PATH": os.path.dirname(os.path.realpath(path)).replace("\\", "/"),
        "TARGET_ARCH": arch_pure,
        "TARGET_ARCH_ABI": arch_abi,
        "TARGET_PLATFORM": f"android-{api}",
        "TARGET_ABI": f"android-{api}-{arch_abi}",
    }


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    subparser = parser.add_subparsers(dest="command", required=True)
    # CMake converter subparser
    convert_parser = subparser.add_parser("convert")
    convert_parser.add_argument("--arch", type=str, help="Target architecture", default="cmake")
    convert_parser.add_argument("--api", type=int, help="Minimum Android API level", default=0)
    convert_parser.add_argument("--no-compat", action="store_true", help='Don\'t change "love" to "luajit" target.')
    convert_parser.add_argument("project", type=str, help="Project name")
    convert_parser.add_argument("input", type=str, help="Android.mk")
    # JSON dump subparser
    dump_parser = subparser.add_parser("dump")
    dump_parser.add_argument("arch", type=str, help="Target architecture")
    dump_parser.add_argument("api", type=int, help="Minimum Android API level")
    dump_parser.add_argument("input", type=str, help="Android.mk")
    # Parse
    args = parser.parse_args()
    # Check command
    if args.command == "convert":
        if args.no_compat:
            substitute_love_with_luajit = False
        target_vars = create_target_vars(args.input, args.arch, args.api)
        with open(args.input, "r", encoding="UTF-8") as f:
            projects = separate_makefiles(f.read())
            print(convert_to_cmake(projects, target_vars, args.project))
    elif args.command == "dump":
        target_vars = create_target_vars(args.input, args.arch, args.api)
        with open(args.input, "r", encoding="UTF-8") as f:
            projects = separate_makefiles(f.read())
            print(convert_to_json(projects, target_vars))
