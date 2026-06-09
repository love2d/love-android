tap = require("tapresearch")

local buttons = {}
local surveyButtons = {}
local buttonWidth = 200
local buttonHeight = 50
local spacing = 10
local labels = { "Survey Wall", "Banner", "Interstitial", "Quick Question", "Send Attributes", "Print Details",
    "Show Surveys" }
local screenWidth, screenHeight
local font
local labelText = "Select an option"
local hasSurveys = false
local showSurveysOverlay = false

local surveysExitButton = {
    x = 40,
    y = 40,
    width = 40,
    height = 40,
    label = "X",
    pressed = false,
    pressTime = 0,
    onClick = function()
        print("[TapResearch-LuaExample] surveysExitButton pressed!")
        showSurveysOverlay = false
    end
}

function showTapResearchContent(placementTag)
    if tap.isReady() then
        tap.onContentShown = function(placement)
            print("[TapResearch-LuaExample] Content shown for placement: " .. placement)
        end
        tap.onContentDismissed = function(placement)
            print("[TapResearch-LuaExample] Content dismissed for placement: " .. placement)
        end
        print("[TapResearch-LuaExample] Showing placement: " .. placementTag)
        tap.showContent(placementTag)
    else
        print("[TapResearch-Lua] TapResearchSDK not ready for placement: " .. placementTag)
    end
end

function showTapResearchSurvey(surveyId, placementTag)
    if tap.isReady() then
        tap.onContentShown = function(placement)
            print("[TapResearch-LuaExample] Content shown for survey: " .. surveyId .. ", placment: " .. placement)
        end
        tap.onContentDismissed = function(placement)
            print("[TapResearch-LuaExample] Content dismissed for survey: " .. surveyId .. ", placement: " .. placement)
        end
        print("[TapResearch-LuaExample] Showing survey: " .. surveyId .. ", placement: " .. placementTag)
		tap.onSurveysRefreshed = function(placement)
			-- Note: Please set this callback where it will be available for the duration of presenting survey buttons on screen.
			--       In this callback you should call to tap.getSurveys and refresh the surveys shown.
			print("[TapResearch-LuaExample] Surveys refreshed for placement: " .. placement)
		end
		tap.showSurvey(surveyId, placementTag)
    else
        print("[TapResearch-Lua] TapResearchSDK not ready for survey: " .. surveyId .. ", placement: " .. placementTag)
    end
end

-- Button press handler functions
function button1()
    updateLabel("Survey Wall selected")
    showTapResearchContent("earn-center")
end

function button2()
    updateLabel("Banner selected")
    showTapResearchContent("banner")
end

function button3()
    updateLabel("Interstitial selected")
    showTapResearchContent("mike-interstitial")
end

function button4()
    updateLabel("Quick Question selected")
    showTapResearchContent("awesome-zone")
end

function button5()
    updateLabel("Send Attributes selected")
    tap.sendUserAttributes({
        user_type = "vip",
        seed_number = 500
    }, true)
end

function button6()
    updateLabel("Print Details selected")
    getPlacementDetails()
end

function dump(value, indent)
    indent = indent or 0

    local spacing = string.rep("  ", indent)

    if type(value) ~= "table" then
        print(spacing .. tostring(value))

        return
    end

    print(spacing .. "{")

    for k, v in pairs(value) do
        io.write(spacing .. "  " .. tostring(k) .. " = ")

        if type(v) == "table" then
            dump(v, indent + 1)
        else
            print(tostring(v))
        end
    end

    print(spacing .. "}")
end

function button7()
    updateLabel("Show Surveys pressed")
    local surveys = tap.getSurveys("earn-center")
    layoutSurveys(surveys)
    -- print("dumping surveys:")
    -- print("surveys type:", type(surveys))
    -- print("surveys value:", surveys)
    -- dump(surveys)
    -- print("done dumping surveys:")
    showSurveysOverlay = true
end

function updateLabel(newText)
    labelText = newText
end

-- Button press handler functions
-- function surveyButtonPressed(survey)
-- tap.showSurvey(survey, "earn-center")
-- end

function layoutSurveys(surveys)
    surveyButtons = {}
    local totalHeight = #labels * buttonHeight + (#labels - 1) * spacing
    local startX = (screenWidth - buttonWidth) / 2
    local startY = (screenHeight - totalHeight) / 2

    for i, survey in ipairs(surveys) do
        local y = startY + (i - 1) * (buttonHeight + spacing)
        local functionName = "surveyButtonPressed"
        local title = survey["rewardAmount"] .. " " .. survey["currencyName"]
        table.insert(surveyButtons, {
            x = startX,
            y = y,
            width = buttonWidth,
            height = buttonHeight,
            label = title,
            pressed = false,
            pressTime = 0,
            onClick = function()
                tap.showSurvey(survey["surveyIdentifier"], "earn-center")
                -- surveyButtonPressed(survey["surveyIdentifier"])
            end
        })
    end
end

-- Position buttons centered vertically and horizontally
local function layoutButtons()
    buttons = {}
    local totalHeight = #labels * buttonHeight + (#labels - 1) * spacing
    local startX = (screenWidth - buttonWidth) / 2
    local startY = (screenHeight - totalHeight) / 2

    for i, label in ipairs(labels) do
        local addButton = true
        if i == 76 then
            if hasSurveys == false then
                addButton = false
            end
        end

        if addButton then
            local y = startY + (i - 1) * (buttonHeight + spacing)
            local functionName = "button" .. i
            table.insert(buttons, {
                x = startX,
                y = y,
                width = buttonWidth,
                height = buttonHeight,
                label = label,
                pressed = false,
                pressTime = 0,
                onClick = function()
                    if _G[functionName] then
                        _G[functionName]()
                    else
                        updateLabel("No handler for " .. label)
                    end
                end
            })
        end
    end
end

function tapRewardHandler(rewards)
    print("[TapResearch-LuaExample] Got rewards!")

    for _, reward in ipairs(rewards) do
        print("  Reward transactionIdentifier: " .. reward.transactionIdentifier)
        print("  Reward placementTag: " .. reward.placementTag)
        print("  Reward placementIdentifier: ", reward.placementIdentifier)
        print("  Reward payoutEvent: ", reward.payoutEvent)
        print("  Reward currencyName: " .. reward.currencyName)
        print("  Reward rewardAmount: " .. tostring(reward.rewardAmount))
    end

    updateLabel("Rewards received!")
end

function tapQQResponseHandler(payload)
    print("[TapResearch-LuaExample] Got QQ payload!")

    print("  Survey ID: ", payload.survey_identifier)
    print("  App Name: ", payload.app_name)
    print("  SDK Version: ", payload.sdk_version)
    print("  Platform: ", payload.platform)
    print("  Placement: ", payload.placement_tag)
    print("  User Locale: ", payload.user_locale)
    print("  Seen At: ", payload.seen_at)

    if payload.questions then
        print("  Questions:")
        for i, q in ipairs(payload.questions) do
            print(string.format("    [%d] %s (%s)", i, q.question_text, q.question_type))
            print("      ID: ", q.question_identifier)
            -- print("      Rating Scale Size: ", tostring(q.rating_scale_size))
            if q.user_answer then
                print("      Answer: ", q.user_answer.value)
                if q.user_answer.identifiers then
                    for _, id in ipairs(q.user_answer.identifiers) do
                        print("        Identifier: ", id)
                    end
                end
            end
        end
    end

    if payload.target_audience then
        print("  Target Audience Filters:")
        for i, f in ipairs(payload.target_audience) do
            print(string.format("    %s %s %s (user: %s)", f.filter_attribute_name, f.filter_operator, f.filter_value,
                f.user_value))
        end
    end

    if payload.complete then
        print("  Survey marked complete:")
        print("    ID: ", payload.complete.complete_identifier)
        print("    At: ", payload.complete.completed_at)
    end

    updateLabel("Got QQ payload!")
end

function getPlacementDetails()
    local details = tap.getPlacementDetails("earn-center")

    if details then
        print("placement details:")
        print("          name: " .. details.name)
        print("  currencyName: " .. details.currencyName)
    else
        print("no details returned")
    end
end

function onTapSdkReady()
    print("[TapResearch-LuaExample] TapResearch Sdk Ready!")
end

function onTapSdkError(error, code)
    print("[TapResearch-LuaExample] TapResearch Sdk Error: " .. code .. ": " .. error)
end

function love.load()
    screenWidth, screenHeight = love.graphics.getDimensions()
    font = love.graphics.newFont(24)
    love.graphics.setFont(font)

    print("[TapResearch-LuaExample] Setting REQUIRED sdk ready and sdk error callbacks")
    tap.onSdkReady = onTapSdkReady
    tap.onTapSdkError = onTapSdkError

    print("[TapResearch-LuaExample] Initializing TapResearchSDK")
    tap.initialize("fb28e5e0572876db0790ecaf6c588598", "tr-sdk-test-user-7887032225")

    print("[TapResearch-LuaExample] Setting reward and Quick Question handlers")
    tap.setOnRewardReceived(tapRewardHandler)
    tap.setOnQuickQuestionResponse(tapQQResponseHandler)

    layoutButtons()
end

function love.resize(w, h)
    screenWidth, screenHeight = w, h
    layoutButtons()
end

-- Main loop
local tapPollingCounter = 60
function love.update(dt)
    -- print("[TapResearch-LuaExample] Update loop!")

    tapPollingCounter = tapPollingCounter - 1
    if tapPollingCounter == 0 then
        if tap.hasSurveys("earn-center") then
            hasSurveys = true
            layoutButtons()
        else
            hasSurveys = false
            tapPollingCounter = 60
        end
    end

    for _, btn in ipairs(buttons) do
        if btn.pressed then
            btn.pressTime = btn.pressTime - dt
            if btn.pressTime <= 0 then
                btn.pressed = false
            end
        end
    end
end

function love.draw()
    -- print("[TapResearch-LuaExample] Draw!")
    if showSurveysOverlay == true then
        if surveysExitButton.pressed then
            love.graphics.setColor(0.8, 0.4, 0.1)
        else
            love.graphics.setColor(1, 0.6, 0.2)
        end
        love.graphics.rectangle("fill", surveysExitButton.x, surveysExitButton.y, surveysExitButton.width,
            surveysExitButton.height, 8, 8)

        love.graphics.setColor(1, 1, 1)
        love.graphics.printf(surveysExitButton.label, surveysExitButton.x,
            surveysExitButton.y + surveysExitButton.height / 2 - font:getHeight() / 2, surveysExitButton.width, "center")


        for _, btn in ipairs(surveyButtons) do
            if btn.pressed then
                love.graphics.setColor(0.1, 0.4, 0.8)
            else
                love.graphics.setColor(0.2, 0.6, 1)
            end
            love.graphics.rectangle("fill", btn.x, btn.y, btn.width, btn.height, 8, 8)

            love.graphics.setColor(1, 1, 1)
            love.graphics.printf(btn.label, btn.x, btn.y + btn.height / 2 - font:getHeight() / 2, btn.width, "center")
        end
    else
        for _, btn in ipairs(buttons) do
            if btn.pressed then
                love.graphics.setColor(0.1, 0.4, 0.8)
            else
                love.graphics.setColor(0.2, 0.6, 1)
            end
            love.graphics.rectangle("fill", btn.x, btn.y, btn.width, btn.height, 8, 8)

            love.graphics.setColor(1, 1, 1)
            love.graphics.printf(btn.label, btn.x, btn.y + btn.height / 2 - font:getHeight() / 2, btn.width, "center")
        end

        -- Draw the label text below buttons
        love.graphics.setColor(1, 1, 1)
        love.graphics.printf(
            labelText,
            0,
            screenHeight - 100,
            screenWidth,
            "center"
        )
    end
end

local function handlePress(x, y)
    if showSurveysOverlay == true then
        for _, btn in ipairs(surveyButtons) do
            if x >= btn.x and x <= btn.x + btn.width and
                y >= btn.y and y <= btn.y + btn.height then
                btn.pressed = true
                btn.pressTime = 0.15
                btn.onClick()
            end
        end
        if x >= surveysExitButton.x and x <= surveysExitButton.x + surveysExitButton.width and
            y >= surveysExitButton.y and y <= surveysExitButton.y + surveysExitButton.height then
            surveysExitButton.pressed = true
            surveysExitButton.pressTime = 0.15
            surveysExitButton.onClick()
        end
    else
        for _, btn in ipairs(buttons) do
            if x >= btn.x and x <= btn.x + btn.width and
                y >= btn.y and y <= btn.y + btn.height then
                btn.pressed = true
                btn.pressTime = 0.15
                btn.onClick()
            end
        end
    end
end

function love.mousepressed(x, y, button)
    if button == 1 then
        handlePress(x, y)
    end
end

function love.touchpressed(id, x, y, dx, dy, pressure)
    local px = x * screenWidth
    local py = y * screenHeight
    handlePress(px, py)
end
