#include "stdafx.h"
/*
#include "Kinect.h"
#include <irrlicht.h>
using namespace irr;
using namespace core;
using namespace video;
using namespace gui;

namespace irr {

    void XN_CALLBACK_TYPE User_NewUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
    {
        CKinect::GetInstance()->User_newUser( generator , nId , pCookie );
    }
  
    void XN_CALLBACK_TYPE User_LostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
    {
        CKinect::GetInstance()->User_lostUser( generator , nId , pCookie );
    }
  
    void XN_CALLBACK_TYPE UserPose_PoseDetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie)
    {
        CKinect::GetInstance()->UserPose_poseDetected( capability , strPose , nId , pCookie );
    }
  
    void XN_CALLBACK_TYPE UserCalibration_CalibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie)
    {
        CKinect::GetInstance()->UserCalibration_calibrationStart( capability , nId , pCookie );
    }
    void XN_CALLBACK_TYPE UserCalibration_CalibrationEnd(xn::SkeletonCapability& capability, XnUserID nId, XnBool bSuccess, void* pCookie)
    {
        CKinect::GetInstance()->UserCalibration_calibrationEnd( capability , nId , bSuccess , pCookie );
    }

    CKinect* CKinect::sInstance = 0;
  
    CKinect::CKinect( void ) : mScaleFactor(0.05f), mIsTracking(false), mLeftLegUp(false), mRightLegUp(false), mRightHandUp(false), mLeftHandUp(false), mStatus(eIdle), mNumCalibrations(0)
    {
        m_bNeedPose = FALSE;
    }
  
    CKinect::~CKinect( void )
    {
        End();
    }
  
    CKinect* CKinect::GetInstance( void )
    {
        if( !sInstance )
            sInstance = new(CKinect);
        return sInstance;
    }
  
    void CKinect::End(void)
    {
        mFile.close();
        m_Context.Shutdown();
    }

    bool CKinect::Init( void )
    {
        mFirstTime = true;

        mIdentityRotation[0] = 1;
        mIdentityRotation[1] = 0;
        mIdentityRotation[2] = 0;
        mIdentityRotation[3] = 0;
        mIdentityRotation[4] = 1;
        mIdentityRotation[5] = 0;
        mIdentityRotation[6] = 0;
        mIdentityRotation[7] = 0;
        mIdentityRotation[8] = 1;

        mKinectOrientations.reserve(12);
        mKinectPositions.reserve(16);

        for ( unsigned int uiCounter = 0; uiCounter < 12; ++uiCounter)
        {
            mKinectOrientations.push_back( XnSkeletonJointOrientation() );
            mConfidencesOrientations[uiCounter] = false;
        }

        for ( unsigned int uiCounter = 0; uiCounter < 16; ++uiCounter)
        {
            mKinectPositions.push_back( XnSkeletonJointPosition() );
            mConfidencesPositions[uiCounter] = false;
        }

        for ( unsigned int uiCounter = 0; uiCounter < mKinectOrientations.size(); ++uiCounter)
        {
            for ( unsigned int uiCounter2 = 0; uiCounter2 < 9; ++uiCounter2)
            {
                mKinectOrientations[uiCounter].orientation.elements[uiCounter2] = mIdentityRotation[uiCounter2];
                mKinectOrientations[uiCounter].fConfidence = 1;
            }
        }

        for ( unsigned int uiCounter = 0; uiCounter < mKinectPositions.size(); ++uiCounter)
        {
            mKinectPositions[uiCounter].position.X = 0;
            mKinectPositions[uiCounter].position.Y = 0;
            mKinectPositions[uiCounter].position.Z = 0;
        }

        mFootCalibration = false;
        mArmsCalibration = false;

        mLeftShoulderY = 0.0f;
        mRightShoulderY = 0.0f;

        XnStatus nRetVal = XN_STATUS_OK;
  
        nRetVal = m_Context.InitFromXmlFile(SAMPLE_XML_PATH);
        if ( !CHECK_RC(nRetVal, "InitFromXml") )
        {
            return false;
        }
  
        nRetVal = m_Context.FindExistingNode(XN_NODE_TYPE_DEPTH, m_DepthGenerator);
        if (!CHECK_RC(nRetVal, "Find depth generator") )
        {
            return false;
        }
        nRetVal = m_Context.FindExistingNode(XN_NODE_TYPE_USER, m_UserGenerator);
  
        if (nRetVal != XN_STATUS_OK)
        {
            nRetVal = m_UserGenerator.Create(m_Context);
            if (!CHECK_RC(nRetVal, "Find user generator"))
            {
                return false;
            }
        }
  
        XnCallbackHandle hUserCallbacks, hCalibrationCallbacks, hPoseCallbacks;
        if (!m_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_SKELETON))
        {
            printf("Supplied user generator doesn't support skeleton\n");
            return false;
        }
  
        m_UserGenerator.RegisterUserCallbacks( User_NewUser, User_LostUser, NULL, hUserCallbacks);
        m_UserGenerator.GetSkeletonCap().RegisterCalibrationCallbacks(UserCalibration_CalibrationStart, UserCalibration_CalibrationEnd, NULL, hCalibrationCallbacks);
  
        if (m_UserGenerator.GetSkeletonCap().NeedPoseForCalibration())
        {
            m_bNeedPose = TRUE;
            if (!m_UserGenerator.IsCapabilitySupported(XN_CAPABILITY_POSE_DETECTION))
            {
                printf("Pose required, but not supported\n");
                return false;
            }
            m_UserGenerator.GetPoseDetectionCap().RegisterToPoseCallbacks(UserPose_PoseDetected, NULL, NULL, hPoseCallbacks);
            m_UserGenerator.GetSkeletonCap().GetCalibrationPose(m_strPose);
        }
  
        m_UserGenerator.GetSkeletonCap().SetSkeletonProfile(XN_SKEL_PROFILE_ALL);
  
        nRetVal = m_Context.StartGeneratingAll();
        if (!CHECK_RC(nRetVal, "StartGenerating"))
        {
            return false;
        }

        return true;
    }

    void CKinect::Update( void )
    {
        xn::SceneMetaData sceneMD;
        xn::DepthMetaData depthMD;
    
        m_Context.WaitAndUpdateAll();
    
        m_DepthGenerator.GetMetaData(depthMD);
        m_UserGenerator.GetUserPixels(0, sceneMD);
    
        char strLabel[50] = "";
        XnUserID aUsers[15];
        XnUInt16 nUsers = 15;
        m_UserGenerator.GetUsers(aUsers, nUsers);
        if ( nUsers == 0)
        {
            mStatus = eIdle;
        }
        bool lAnyCalibration = false;
        for (int i = 0; i < nUsers; ++i)
        {
            if ( m_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i]) )
            {
                lAnyCalibration = true;
            }
            if ( nUsers)
            if (m_bPrintID)
            {
                XnPoint3D com;
                m_UserGenerator.GetCoM(aUsers[i], com);
                m_DepthGenerator.ConvertRealWorldToProjective(1, &com, &com);
            }

            if (m_bDrawSkeleton && m_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i]))
            {
                if (!m_UserGenerator.GetSkeletonCap().IsTracking(aUsers[i]))
                {
                    printf("not tracked!\n");
                    return;
                }

                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_TORSO            , mKinectPositions[eBoneTorso]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_ELBOW      , mKinectPositions[eBoneRightElbow]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_SHOULDER   , mKinectPositions[eBoneRightShoulder]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_HAND       , mKinectPositions[eBoneRightHand]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_ELBOW       , mKinectPositions[eBoneLeftElbow]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_SHOULDER    , mKinectPositions[eBoneLeftShoulder]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_HAND        , mKinectPositions[eBoneLeftHand]);
                                                                                                              
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_HIP         , mKinectPositions[eBoneLeftHip]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_KNEE        , mKinectPositions[eBoneLeftKnee]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_LEFT_FOOT        , mKinectPositions[eBoneLeftFoot]);
                                                                                                              
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_HIP        , mKinectPositions[eBoneRightHip]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_KNEE       , mKinectPositions[eBoneRightKnee]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointPosition(aUsers[i], XN_SKEL_RIGHT_FOOT       , mKinectPositions[eBoneRightFoot]);
                                                                                                              
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_TORSO         , mKinectOrientations[eBoneTorso]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_ELBOW    , mKinectOrientations[eBoneLeftElbow]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_SHOULDER , mKinectOrientations[eBoneLeftShoulder]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_HIP      , mKinectOrientations[eBoneLeftHip]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_LEFT_KNEE     , mKinectOrientations[eBoneLeftKnee]);

                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_ELBOW   , mKinectOrientations[eBoneRightElbow]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_SHOULDER, mKinectOrientations[eBoneRightShoulder]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_HIP     , mKinectOrientations[eBoneRightHip]);
                m_UserGenerator.GetSkeletonCap().GetSkeletonJointOrientation(aUsers[i], XN_SKEL_RIGHT_KNEE    , mKinectOrientations[eBoneRightKnee]);

                mKinectOrientations[3] = mKinectOrientations[eBoneTorso];
                mKinectOrientations[6] = mKinectOrientations[eBoneTorso];
                mKinectOrientations[9] = mKinectOrientations[eBoneTorso];

                if ( mFirstTime )
                {
                    mConfidencesPositions[eBoneTorso         ] = mConfidencesPositions[eBoneTorso         ] ? true : ((mKinectPositions[eBoneTorso         ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneLeftShoulder  ] = mConfidencesPositions[eBoneLeftShoulder  ] ? true : ((mKinectPositions[eBoneLeftShoulder  ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneLeftElbow     ] = mConfidencesPositions[eBoneLeftElbow     ] ? true : ((mKinectPositions[eBoneLeftElbow     ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneLeftHip       ] = mConfidencesPositions[eBoneLeftHip       ] ? true : ((mKinectPositions[eBoneLeftHip       ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneLeftKnee      ] = mConfidencesPositions[eBoneLeftKnee      ] ? true : ((mKinectPositions[eBoneLeftKnee      ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneRightShoulder ] = mConfidencesPositions[eBoneRightShoulder ] ? true : ((mKinectPositions[eBoneRightShoulder ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneRightElbow    ] = mConfidencesPositions[eBoneRightElbow    ] ? true : ((mKinectPositions[eBoneRightElbow    ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneRightHip      ] = mConfidencesPositions[eBoneRightHip      ] ? true : ((mKinectPositions[eBoneRightHip      ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneRightKnee     ] = mConfidencesPositions[eBoneRightKnee     ] ? true : ((mKinectPositions[eBoneRightKnee     ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneRightHand     ] = mConfidencesPositions[eBoneRightHand     ] ? true : ((mKinectPositions[eBoneRightHand     ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneLeftHand      ] = mConfidencesPositions[eBoneLeftHand      ] ? true : ((mKinectPositions[eBoneLeftHand      ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneRightFoot     ] = mConfidencesPositions[eBoneRightFoot     ] ? true : ((mKinectPositions[eBoneRightFoot     ].fConfidence == 1) ? true : false);
                    mConfidencesPositions[eBoneLeftFoot      ] = mConfidencesPositions[eBoneLeftFoot      ] ? true : ((mKinectPositions[eBoneLeftFoot      ].fConfidence == 1) ? true : false);

                    if (mConfidencesPositions[eBoneTorso])
                    {
                        mStartPosition.set( mKinectPositions[eBoneTorso].position.X,
                                            mKinectPositions[eBoneTorso].position.Y,
                                            mKinectPositions[eBoneTorso].position.Z);
                    }

                    if (mConfidencesPositions[eBoneRightFoot] &&
                        mConfidencesPositions[eBoneLeftFoot ] &&
                        !mFootCalibration)
                    {
                        mMiddlePositionLeftLeg  = mKinectPositions[eBoneLeftFoot ].position.Y;
                        mMiddlePositionRightLeg = mKinectPositions[eBoneRightFoot].position.Y;
                        mFootCalibration = true;
                    }

                    if (mConfidencesPositions[eBoneLeftShoulder ] &&
                        mConfidencesPositions[eBoneRightShoulder] &&
                        !mArmsCalibration)
                    {
                        mLeftShoulderY  = mKinectPositions[eBoneLeftShoulder ].position.Y;
                        mRightShoulderY = mKinectPositions[eBoneRightShoulder].position.Y;
                        mArmsCalibration = true;
                    }

                    if (mArmsCalibration && 
                        mFootCalibration && 
                        mConfidencesPositions[eBoneTorso     ] && 
                        mConfidencesPositions[eBoneLeftKnee  ] &&
                        mConfidencesPositions[eBoneRightKnee ] &&
                        mConfidencesPositions[eBoneLeftHand  ] &&
                        mConfidencesPositions[eBoneLeftElbow ] &&
                        mConfidencesPositions[eBoneRightHand ] &&
                        mConfidencesPositions[eBoneRightElbow] )
                    {
                        mFirstTime = false;
                        
                        float lAux = mKinectPositions[eBoneRightHip].position.Y + mKinectPositions[eBoneLeftHip].position.Y + mKinectPositions[eBoneTorso].position.Y;
                        lAux *= 0.333333f;
                         mStartPosition.Y = lAux;
                    }
                }
                else
                {
                    if ( mKinectPositions[eBoneLeftFoot].fConfidence )
                    {
                        float mPosLeftFoot = mKinectPositions[eBoneLeftFoot].position.Y;
                        mMiddlePositionLeftLeg = (mPosLeftFoot < mMiddlePositionLeftLeg) ? mPosLeftFoot : mMiddlePositionLeftLeg;
                        mLeftLegUp  = ( mPosLeftFoot > mMiddlePositionLeftLeg + 200 ) ? true : false;
                    }

                    if ( mKinectPositions[eBoneRightFoot].fConfidence )
                    {
                        float mPosRightFoot = mKinectPositions[eBoneRightFoot].position.Y;
                        mMiddlePositionLeftLeg = (mPosRightFoot < mMiddlePositionRightLeg) ? mPosRightFoot : mMiddlePositionRightLeg;
                        mRightLegUp  = ( mPosRightFoot > mMiddlePositionRightLeg + 200 ) ? true : false;
                    }

                    mCorePosition.X = mKinectPositions[eBoneTorso].position.X - mStartPosition.X;
                    mCorePosition.Z = mKinectPositions[eBoneTorso].position.Z - mStartPosition.Z;

                    if ( mKinectPositions[eBoneRightHip].fConfidence &&
                         mKinectPositions[eBoneLeftHip ].fConfidence &&
                         mKinectPositions[eBoneTorso   ].fConfidence )
                    {
                        float lAux = mKinectPositions[eBoneRightHip].position.Y + mKinectPositions[eBoneLeftHip].position.Y + mKinectPositions[eBoneTorso].position.Y;
                        lAux *= 0.333333f;
                        mCorePosition.Y = lAux - mStartPosition.Y;
                    }
                }

                mIsTracking = true;
            }
        }
    }

    void CKinect::User_newUser( xn::UserGenerator& generator, XnUserID nId, void* pCookie )
    {
        printf("New User %d\n", nId);
        // New user found
        if (m_bNeedPose)
        {
            m_UserGenerator.GetPoseDetectionCap().StartPoseDetection(m_strPose, nId);
        }
        else
        {
            m_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
        }
    }
  
    // Callback: An existing user was lost
    void CKinect::User_lostUser(xn::UserGenerator& generator, XnUserID nId, void* pCookie)
    {
        printf("Lost user %d\n", nId);
    }
    // Callback: Detected a pose
    void CKinect::UserPose_poseDetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie)
    {
        printf("Pose %s detected for user %d\n", strPose, nId);
        m_UserGenerator.GetPoseDetectionCap().StopPoseDetection(nId);
        m_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
    }
    // Callback: Started calibration
    void CKinect::UserCalibration_calibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie)
    {
        printf("Calibration started for user %d\n", nId);
        mStatus = eCalibrating;
        mNumCalibrations++;

    }
    // Callback: Finished calibration
    void CKinect::UserCalibration_calibrationEnd(xn::SkeletonCapability& capability, XnUserID nId, XnBool bSuccess, void* pCookie)
    {
        if (bSuccess)
        {
            // Calibration succeeded
            printf("Calibration complete, start tracking user %d\n", nId);
            m_UserGenerator.GetSkeletonCap().StartTracking(nId);
            if ( mNumCalibrations > 0)
                mStatus = eCalibrated;
        }
        else
        {
            mNumCalibrations--;
            // Calibration failed
            printf("Calibration failed for user %d\n", nId);
            mStatus = eIdle;
            if (m_bNeedPose)
            {
                m_UserGenerator.GetPoseDetectionCap().StartPoseDetection(m_strPose, nId);
            }
            else
            {
                m_UserGenerator.GetSkeletonCap().RequestCalibration(nId, TRUE);
            }
        }
    }
  
    core::vector3df CKinect::GetCorePosition(void)
    {
        return (mCorePosition*mScaleFactor);
    }

    CKinect::sMatrixRotations CKinect::GetInitialRotationForBone( scene::IBoneSceneNode *bone )
    {
        sMatrixRotations iRotation;

        core::vector3df lInitRot = bone->getRotation();
        iRotation.InitialRotationMatrix.setRotationDegrees(lInitRot);
        
        std::vector< core::matrix4 > lMatrixVector;
        lMatrixVector.push_back( iRotation.InitialRotationMatrix );
        while (bone->getParent() != 0)
        {
            bone = static_cast<scene::IBoneSceneNode *>(bone->getParent());
            if (strcmp( bone->getName(), "") != 0)
            {
                core::matrix4 lMatrixAuxiliar;
                lMatrixAuxiliar.setRotationDegrees(bone->getRotation());
                lMatrixVector.push_back( lMatrixAuxiliar );
            }
        }

        int iCounter = lMatrixVector.size() - 1;
        for (; iCounter >= 0; iCounter -= 1)
        {
            core::vector3df a = lMatrixVector[iCounter].getRotationDegrees();
            iRotation.WorldToLocal = iRotation.WorldToLocal * lMatrixVector[iCounter];
        }

        iRotation.WorldToLocal.getInverse(iRotation.InvWorldToLocal);

        return iRotation;

    }

    bool CKinect::GetRotationTorso( core::vector3df& aRotation )
    {
        bool lFiable = (mKinectOrientations[eBoneTorso].fConfidence == 1) ? true : false;
        
        if ( !lFiable )
        {
            return false;
        }

        float *lRotMatKBone3x3      = mKinectOrientations[eBoneTorso].orientation.elements;
        
        core::matrix4 lRotMatKBone4x4;

        lRotMatKBone4x4[0] = lRotMatKBone3x3[0];        lRotMatKBone4x4[4] = lRotMatKBone3x3[3];        lRotMatKBone4x4[8]  = lRotMatKBone3x3[6];
        lRotMatKBone4x4[1] = lRotMatKBone3x3[1];        lRotMatKBone4x4[5] = lRotMatKBone3x3[4];        lRotMatKBone4x4[9]  = lRotMatKBone3x3[7];
        lRotMatKBone4x4[2] = lRotMatKBone3x3[2];        lRotMatKBone4x4[6] = lRotMatKBone3x3[5];        lRotMatKBone4x4[10] = lRotMatKBone3x3[8];

        core::vector3df lRotMatKBone4x4Degrees = lRotMatKBone4x4.getRotationDegrees();
        lRotMatKBone4x4Degrees.X = -lRotMatKBone4x4Degrees.X;

        aRotation = lRotMatKBone4x4Degrees;

        return true;
    }

    bool CKinect::GetRotation( EBoneNames eBone, core::vector3df& aRotation )
    {
        bool lFiable = (mKinectOrientations[eBone].fConfidence == 1) ? true : false;
        if ( !lFiable )
        {
            return false;
        }

        float *lRotMatKBone3x3      = mKinectOrientations[eBone].orientation.elements;
        float *lRotMatKParent3x3    = mKinectOrientations[eBone - 1].orientation.elements;

        core::matrix4 lRotMatKBone4x4;
        core::matrix4 lRotMatKParent4x4;

        lRotMatKBone4x4[0] = lRotMatKBone3x3[0];        lRotMatKBone4x4[4] = lRotMatKBone3x3[3];        lRotMatKBone4x4[8]  = lRotMatKBone3x3[6];
        lRotMatKBone4x4[1] = lRotMatKBone3x3[1];        lRotMatKBone4x4[5] = lRotMatKBone3x3[4];        lRotMatKBone4x4[9]  = lRotMatKBone3x3[7];
        lRotMatKBone4x4[2] = lRotMatKBone3x3[2];        lRotMatKBone4x4[6] = lRotMatKBone3x3[5];        lRotMatKBone4x4[10] = lRotMatKBone3x3[8];

        lRotMatKParent4x4[0] = lRotMatKParent3x3[0];    lRotMatKParent4x4[4] = lRotMatKParent3x3[3];    lRotMatKParent4x4[8]  = lRotMatKParent3x3[6];
        lRotMatKParent4x4[1] = lRotMatKParent3x3[1];    lRotMatKParent4x4[5] = lRotMatKParent3x3[4];    lRotMatKParent4x4[9]  = lRotMatKParent3x3[7];
        lRotMatKParent4x4[2] = lRotMatKParent3x3[2];    lRotMatKParent4x4[6] = lRotMatKParent3x3[5];    lRotMatKParent4x4[10] = lRotMatKParent3x3[8];

        core::vector3df boneRotationKDegrees        = lRotMatKBone4x4.getRotationDegrees();
        core::vector3df parentRotationKDegrees      = lRotMatKParent4x4.getRotationDegrees();

        core::matrix4 lRotMatKParentInverse;
        lRotMatKParent4x4.getInverse(lRotMatKParentInverse);
        core::matrix4 mMatrixParentMultBone = lRotMatKBone4x4 * lRotMatKParentInverse;

        core::vector3df mParentMultBoneDegrees = mMatrixParentMultBone.getRotationDegrees();
        mParentMultBoneDegrees.X = -mParentMultBoneDegrees.X;
        mMatrixParentMultBone.setRotationDegrees(mParentMultBoneDegrees);

        sMatrixRotations lInitialRotations = mInitialMatrixRotation[eBone];
        
        core::matrix4 transform1 = lInitialRotations.WorldToLocal * mMatrixParentMultBone;
        core::matrix4 transform2 = transform1 * lInitialRotations.InvWorldToLocal;

        core::vector3df previewVector = transform2.getRotationDegrees();

        core::matrix4 mMatrixResultMultInitial = lInitialRotations.InitialRotationMatrix * transform2;

        aRotation = mMatrixResultMultInitial.getRotationDegrees();

        return true;
    }

    void CKinect::setInitialRotations( scene::IAnimatedMeshSceneNode *player )
    {
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("bone3"     ) ) );     // "torso"      
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("lshoulder" ) ) );     // "lshoulder"
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("lelbow"    ) ) );     // "lelbow"   

        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("bone3"     ) ) );     // "torso"
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("lhip"      ) ) );     // "lhip"   
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("lknee"     ) ) );     // "lknee"    

        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("bone3"     ) ) );     // "torso"
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("rshoulder" ) ) );     // "rshoulder
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("relbow"    ) ) );     // "relbow"  

        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("bone3"     ) ) );     // "torso"
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("rhip"      ) ) );     // "rhip"    
        mInitialMatrixRotation.push_back( GetInitialRotationForBone( player->getJointNode("rknee"     ) ) );     // "rknee"    
    }

    bool CKinect::isInTPose(void)
    {
        if (!(mKinectPositions[eBoneLeftShoulder ].fConfidence && 
              mKinectPositions[eBoneRightShoulder].fConfidence &&
              mKinectPositions[eBoneLeftElbow    ].fConfidence &&
              mKinectPositions[eBoneRightElbow   ].fConfidence &&
              mKinectPositions[eBoneLeftHand     ].fConfidence &&
              mKinectPositions[eBoneRightHand    ].fConfidence))
        {
            return false;
        }

        float lLeftShoulderYMax = mKinectPositions[eBoneLeftShoulder].position.Y + 200;
        float lLeftShoulderYMin = mKinectPositions[eBoneLeftShoulder].position.Y - 200;
        
        float lRightShoulderYMax = mKinectPositions[eBoneRightShoulder].position.Y + 200;
        float lRightShoulderYMin = mKinectPositions[eBoneRightShoulder].position.Y - 200;

        float lRightElbowY = mKinectPositions[eBoneRightElbow].position.Y;
        float lRightHandY  = mKinectPositions[eBoneRightHand ].position.Y;
        
        float lLeftElbowY = mKinectPositions[eBoneLeftElbow].position.Y;
        float lLeftHandY  = mKinectPositions[eBoneLeftHand ].position.Y;

        if (lRightElbowY < lRightShoulderYMax &&
            lRightElbowY > lRightShoulderYMin &&
            lRightHandY  < lRightShoulderYMax &&
            lRightHandY  > lRightShoulderYMin )
        {
            mRightHandUp = true;
        }
        else
        {
            mRightHandUp = false;
        }

        if (lLeftElbowY < lLeftShoulderYMax &&
            lLeftElbowY > lLeftShoulderYMin &&
            lLeftHandY  < lLeftShoulderYMax &&
            lLeftHandY  > lLeftShoulderYMin )
        {
            mLeftHandUp = true;
        }
        else
        {
            mLeftHandUp = false;
        }

        return (mLeftHandUp && mRightHandUp);
    }

    unsigned int CKinect::LegsPosition( void )
    {
        if (mRightLegUp && mLeftLegUp)
        {
            return 3;
        }
        if (mRightLegUp && !mLeftLegUp)
        {
            return 2;
        }
        if (!mRightLegUp && mLeftLegUp)
        {
            return 1;
        }
        return 0;
    }

    CKinect::EKinectStatus CKinect::GetStatus( void )
    {
        return mStatus;
    }

    void CKinect::ForceStatus()
    {
        mStatus = eIdle;
    }

} //namespace irr

*/