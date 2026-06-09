-- tapresearch.lua
local tapresearch = {}

-- Load the native bindings
local native = require("tapresearch_native")

function tapresearch.initialize(apiToken, userId)
    assert(type(apiToken) == "string", "apiToken must be a string")
    assert(type(userId) == "string", "userId must be a string")
    native.initialize(apiToken, userId)
end

function initializeWithUserAttributes(apiToken, userId, attributes, clear)
    assert(type(apiToken) == "string", "apiToken must be a string")
    assert(type(userId) == "string", "userId must be a string")
	assert(type(attributes) == "table", "attributes must be a table")
	assert(type(clear) == "boolean", "clear must be a boolean")
    native.initializeWithUserAttributes(apiToken, userId, attributes, clear)
end

function tapresearch.isReady()
    return native.isReady()
end

function tapresearch.setUserIdentifier(userId)
    assert(type(userId) == "string", "placement must be a string")
    return native.setUserIdentifier(userId)
end

function tapresearch.sendUserAttributes(attributes, clear)
	assert(type(attributes) == "table", "attributes must be a table")
	assert(type(clear) == "boolean", "clear must be a boolean")
	return native.sendUserAttributes(attributes, clear)
end

function tapresearch.hasSurveys(placementTag)
	assert(type(placementTag) == "string", "placementTag must be a string")
	return native.hasSurveys(placementTag)
end

function tapresearch.canShow(placementTag)
	assert(type(placementTag) == "string", "placementTag must be a string")
	return native.canShow(placementTag)
end

function tapresearch.showContent(placementTag)
    assert(type(placementTag) == "string", "placementTag must be a string")
    native.showContent(placementTag)
end

function showContentWithCustomParameters(placementTag, attributes)
    assert(type(placementTag) == "string", "placementTag must be a string")
 	assert(type(parameters) == "table", "attributes must be a table")
    native.showContentWithCustomParameters(placement, attributes)
end

function tapresearch.showSurvey(surveyId, placementTag)
	assert(type(surveyId) == "string", "surveyId must be a string")
	assert(type(placementTag) == "string", "placementTag must be a string")
	native.showSurvey(surveyId, placementTag)
end

function showSurveyWithCustomParameters(surveyId, placementTag, attributes)
	assert(type(surveyId) == "string", "surveyId must be a string")
	assert(type(placementTag) == "string", "placementTag must be a string")
	assert(type(parameters) == "table", "attributes must be a table")
	native.showContentWithCustomParameters(survey, placementTag, attributes)
end

function tapresearch.getSurveys(placementTag)
	assert(type(placementTag) == "string", "placementTag must be a string")
	return native.getSurveys(placementTag)
end

function tapresearch.grantBoost(boostTag)
	assert(type(boostTag) == "string", "boostTag must be a string")
	native.grantBoost(boostTag)
end

function tapresearch.getPlacementDetails(placementTag)
	assert(type(placementTag) == "string", "placementTag must be a string")
	return native.getPlacementDetails(placementTag)
end

-- The SDK needs to know when a reward or Quick Question callback is set, to make sure this happens
-- we use a setter to set the relevant callback.
function tapresearch.setOnRewardReceived(func)
    tapresearch.onRewardReceived = func
    if func == nil then
        native.setRewardCallback(false)
    else 
        native.setRewardCallback(true)
    end
end

function tapresearch.setOnQuickQuestionResponse(func)
    tapresearch.onQuickQuestionReceived = func
	if func == nil then
		native.setQuickQuestionCallback(false)
	else
		native.setQuickQuestionCallback(true)
	end
end

-- The delegate callback functions below should be overridden in your own code.
-- For example when you need to have a local onContentShown callback you can use something similar to this:
--
-- tap.onContentShown = function(placement)
--     -- Handle content shown, un-pause game for example... 
-- end
--
-- Note: The native bridge still gets called by the SDK for relevant callbacks so make sure that you have 
--       your own callback handlers set!!!

-- Called from native when rewards are received
function tapresearch.onRewardReceived(rewards)
    print("[LuaToNativeBridge] Got rewards! You MUST override this function with your own!")
end

-- Called from native when a Quick Question is received
function tapresearch.onQuickQuestionReceived(payload)
	print("[LuaToNativeBridge] Got QQ! You MUST override this function with your own!")
end

-- Unused functions as examples

-- Called from native when content is shown
--function tapresearch.onContentShown(placement)
--    print("[LuaToNativeBridge] Content shown for: " .. placement)
--end

-- Called from native when content is dismissed
--function tapresearch.onContentDismissed(placement)
--    print("[LuaToNativeBridge] Content dismissed for: " .. placement)
--end

-- Called from native when the SDK is ready
---function tapresearch.onSdkReady() 
--    print("[LuaToNativeBridge] Sdk Ready!")
---end

-- Called form native when surveys for a placement are refreshed
--function tapresearch.onSurveysRefreshed(placement)
--    print("[LuaToNativeBridge] Content shown for: " .. placement)
--end

-- Called from native when there is an error
---function tapresearch.onSdkError(error, code)
---    print("[LuaToNativeBridge] Sdk Eror: " .. code .. ": " .. error)
---end

return tapresearch
