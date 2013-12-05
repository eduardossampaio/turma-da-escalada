#pragma once
/*
//---------------------------------------------------------------------------
// Defines Kinect
//---------------------------------------------------------------------------
#define SAMPLE_XML_PATH "SamplesConfig.xml"

//---------------------------------------------------------------------------
// Includes Kinect
//---------------------------------------------------------------------------
#include <OpenNi.h>
#include <Nite.h>



#pragma comment( lib, "openNI.lib" )

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include <irrlicht.h>

namespace irr {

    class IAnimatedMeshSceneNode;
    class CKinect
    {
      public:

        enum EKinectStatus
        {
            eIdle,
            eCalibrating,
            eCalibrated
        };

        enum EBoneNames
        {
            eBoneTorso         = 0,                   // "torso"
            eBoneLeftShoulder  = 1,                   // "lshoulder"
            eBoneLeftElbow     = 2,                   // "lelbow"   
                                                      //3torso
            eBoneLeftHip       = 4,                   // "lhip"   
            eBoneLeftKnee      = 5,                   // "lknee"     
                                                      //6torso
            eBoneRightShoulder = 7,                   // "rshoulder"
            eBoneRightElbow    = 8,                   // "relbow"   
                                                      //9torso
            eBoneRightHip      = 10,                  // "rhip"
            eBoneRightKnee     = 11,                  // "rknee"

            eBoneRightHand     = 12,                  // no te bone
            eBoneLeftHand      = 13,                  // no te bone

            eBoneRightFoot     = 14,                  // no te bone
            eBoneLeftFoot      = 15,                  // no te bone

        };

        struct InitialRotation
        {
            core::quaternion    WorldToLocal;
            core::quaternion    InvWorldToLocal;
            core::vector3df     InitialRotationVector;
        };

        struct sMatrixRotations
        {
            core::matrix4    WorldToLocal;
            core::matrix4    InvWorldToLocal;
            core::matrix4    InitialRotationMatrix;
        };

        unsigned int mNumCalibrations;

        bool Init( void );
        void setInitialRotations( scene::IAnimatedMeshSceneNode *player );

        unsigned int LegsPosition(void);

        void Update( void );
        void End(void);
 
        static CKinect* GetInstance( void );
        EKinectStatus GetStatus( void );
        void ForceStatus( void );
    
        //Callbacks
        void User_newUser( xn::UserGenerator& generator, XnUserID nId, void* pCookie );
        void User_lostUser( xn::UserGenerator& generator, XnUserID nId, void* pCookie );
        void UserPose_poseDetected(xn::PoseDetectionCapability& capability, const XnChar* strPose, XnUserID nId, void* pCookie);
        void UserCalibration_calibrationStart(xn::SkeletonCapability& capability, XnUserID nId, void* pCookie);
        void UserCalibration_calibrationEnd(xn::SkeletonCapability& capability, XnUserID nId, XnBool bSuccess, void* pCookie);

        core::vector3df GetCorePosition(void);
        core::vector3df GetBoneLocalRotation( EBoneNames eBone, scene::IBoneSceneNode *bone );
        void IncrementaAngle(void);

        bool GetRotation( EBoneNames eBone, core::vector3df& aRotation );
        bool GetRotationTorso(core::vector3df& aRotation);
        bool isInTPose(void);
        bool isTracking(void);

        ~CKinect( void );
      private:

        CKinect( void );
    
        inline bool CHECK_RC( XnStatus nRetVal, const char *what)
        {
          if (nRetVal != XN_STATUS_OK)
          {
            printf("%s failed: %s\n", what, xnGetStatusString(nRetVal));
            return false;
          }
          return true;
        }

        sMatrixRotations GetInitialRotationForBone( scene::IBoneSceneNode *bone );

        static CKinect* sInstance;

        xn::Context         m_Context;
        xn::DepthGenerator  m_DepthGenerator;
        xn::UserGenerator   m_UserGenerator;

        XnBool m_bDrawSkeleton;
        XnBool m_bPrintID;
        XnBool m_bNeedPose;
        XnChar m_strPose[20];

        const float mScaleFactor;
        std::ofstream mFile;
        bool mIsTracking;
        core::matrix4 mRotationMatrix;

        std::vector< InitialRotation            > mInitialRotations;
        std::vector< sMatrixRotations           > mInitialMatrixRotation;
        std::vector< XnSkeletonJointPosition    > mKinectPositions;
        std::vector< XnSkeletonJointOrientation > mKinectOrientations;
        
        float mIdentityRotation[9];

        bool mFirstTime;
        bool mLeftLegUp;
        bool mRightLegUp;

        float mMiddlePositionLeftLeg;
        float mMiddlePositionRightLeg;

        float mLeftShoulderY;
        float mRightShoulderY;

        bool mConfidencesPositions[16];
        bool mConfidencesOrientations[12];
        bool mFootCalibration;
        bool mArmsCalibration;

        bool mRightHandUp;
        bool mLeftHandUp;

        EKinectStatus mStatus;

        core::vector3df mStartPosition;
        core::vector3df mCorePosition;

    };
}
*/