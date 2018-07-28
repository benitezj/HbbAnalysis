export CXTAG=${PWD##*/}
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh
source ${ATLAS_LOCAL_ROOT_BASE}/packageSetups/atlasLocalDQ2ClientSetup.sh --skipConfirm --dq2ClientVersion ${dq2ClientVersionVal}
echo ${VOMSPASSWD} | voms-proxy-init --pwstdin -voms atlas
source ${ATLAS_LOCAL_ROOT_BASE}/packageSetups/atlasLocalPandaClientSetup.sh --pandaClientVersion ${pandaClientVersionVal}  currentJedi --noAthenaCheck
source $ATLAS_LOCAL_RCSETUP_PATH/rcSetup.sh
source ${ATLAS_LOCAL_ROOT_BASE}/packageSetups/atlasLocalPyAmiSetup.sh --pyAMIVersion ${pyAMIVersionVal}
