package com.tapresearch.love;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import com.tapresearch.tapsdk.TapResearch;
import com.tapresearch.tapsdk.callback.TRContentCallback;
import com.tapresearch.tapsdk.callback.TRErrorCallback;
import com.tapresearch.tapsdk.callback.TRQQDataCallback;
import com.tapresearch.tapsdk.callback.TRRewardCallback;
import com.tapresearch.tapsdk.models.QQPayload;
import com.tapresearch.tapsdk.models.TRPlacementDetails;
import com.tapresearch.tapsdk.models.TRReward;
import com.tapresearch.tapsdk.models.TRSurvey;

import java.util.HashMap;
import java.util.List;

public class TapResearchLoveBridge {
    private static final String TAG = "TapResearchLoveBridge";

    public static void setActivity(Activity activity) {
        setAttributes(activity);
    }

    public static void initialize(String apiToken, String userId) {

        Log.d(TAG,"initialize");
        TapResearch.INSTANCE.initialize(
                apiToken,
                userId,
                (TRRewardCallback) rewards -> {
                    Log.d(TAG, "Received rewards: " + rewards);
                    nativeOnRewardReceived(rewards.toArray(new TRReward[0]));
                },
                (TRErrorCallback) trError -> {
                    Log.e(TAG, "TapResearch Error: " + trError.getDescription());
                    nativeOnSdkError(trError.getDescription(), trError.getCode());
                },
                () -> {
                    Log.d(TAG, "TapResearch SDK Ready");
                    nativeOnSdkReady();
                },
                new TRQQDataCallback() {
                    @Override
                    public void onQuickQuestionDataReceived(QQPayload qqPayload) {
                        Log.d(TAG, "onQuickQuestionDataReceived: " + qqPayload);
                        nativeOnQuickQuestionResponse(qqPayload);
                    }
                },
                null
        );
    }

    public static boolean isReady() {
        return TapResearch.INSTANCE.isReady();
    }

    public static void setUserIdentifier(String userId) {
        TapResearch.INSTANCE.setUserIdentifier(userId);
    }

    public static void sendUserAttributes(HashMap<String, Object> attributes, boolean clear) {
        Log.d(TAG, "sendUserAttributes: " + attributes + " clear: " + clear);
        TapResearch.INSTANCE.sendUserAttributes(attributes, clear, error -> {
             if (error != null) {
                 // not implemented
            }
        });
    }

    public static boolean canShowContent(String placementTag) {
        return TapResearch.INSTANCE.canShowContentForPlacement(placementTag, trError -> {
            // error handler not implemented
        });
    }

    public static void showContent(String placementTag) {
        TapResearch.INSTANCE.showContentForPlacement(
                placementTag,
                new TRContentCallback() {
                    @Override
                    public void onTapResearchContentShown(String placementTag) {
                        nativeOnContentShown(placementTag);
                    }

                    @Override
                    public void onTapResearchContentDismissed(String placementTag) {
                        nativeOnContentDismissed(placementTag);
                    }
                },
                null,
                trError -> {
                    // not implemented
                }
        );
    }

    public static boolean hasSurveys(String placementTag) {
        return TapResearch.INSTANCE.hasSurveysForPlacement(placementTag,
                trError -> {
                    // not implemented
                }
        );
    }

    public static void showSurvey(String surveyId, String placementTag) {
        TapResearch.INSTANCE.showSurveyForPlacement(placementTag, surveyId,
                null, null,
                trError -> {
                    // not implemented
                });
    }

    public static TRSurvey[] getSurveys(String placementTag) {
        List<TRSurvey> surveys = TapResearch.INSTANCE.getSurveysForPlacement(placementTag,
                trError -> {
                    // not implemented
                });
        if (surveys == null) {
            return new TRSurvey[0];
        }
        return surveys.toArray(new TRSurvey[0]);
    }

    public static TRPlacementDetails getPlacementDetails(String placementTag) {
        return TapResearch.INSTANCE.getPlacementDetails(placementTag,
                trError -> {
                    // not implemented
                });
    }

    private static void setAttributes(Context context) {
        new Thread() {
            @Override
            public void run() {
                try {
                    context.getSharedPreferences("tr_orca_params", 0).edit()
                            .putString("dev_platform", "love")
                            .putString("dev_version", "3.7.0--rc0")
                            .putString("dev_engine_version", "11.5").apply();
                    Log.d(TAG,"setAttributes:  set dev_platform, dev_version, dev_engine_version");
                }catch(Throwable _){}
            }
        }.start();
    }

    // Native methods
    private static native void nativeOnRewardReceived(TRReward[] rewards);
    private static native void nativeOnSdkError(String message, int code);
    private static native void nativeOnSdkReady();
    private static native void nativeOnContentShown(String placementTag);
    private static native void nativeOnContentDismissed(String placementTag);
    private static native void nativeOnQuickQuestionResponse(QQPayload payload);
}
