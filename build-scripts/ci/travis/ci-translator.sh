




# See if this is a CI environment.
# Travis has both CI and CONTINUOUS_INTEGRATION set to "true"
if [[ "${CI}" == "true" || "${CONTINUOUS_INTEGRATION}" == "true" ]]; then
     printf "This is a continuous integration environment."
else
     printf "This is not a continuous integration environment."
fi


# CI_HOST
if [[ "${TRAVIS}" == "true" ]]; then
     export CI_HOST="travis"
else
     printf "Unable to determine CI host."
fi

# 
export CI_HAS_JOSH_K_SEAL_OF_APPROVAL="${HAS_JOSH_K_SEAL_OF_APPROVAL}"


# 
export CI_REPOSITORY_BRANCH="${_TRAVIS_BRANCH}"


# 
export CI_BUILD_DIRECTORY="${TRAVIS_BUILD_DIR}"


# 
export CI_BIULD_ID="${TRAVIS_BUILD_ID}"


# 
export CI_BUILD_NUMBER="${TRAVIS_BUILD_NUMBER}"


# 
export CI_REPOSITORY_PULL_ID="${TRAVIS_COMMIT}"


# 
export CI_REPOSITORY_PULL_RANGE="${TRAVIS_COMMIT_RANGE}"


# 
export CI_JOB_ID="${TRAVIS_JOB_ID}"


# 
export CI_JOB_NUMBER="${TRAVIS_JOB_NUMBER}"


# CI_PULL_REQUEST_BOOLEAN
if [[ "${TRAVIS_PULL_REQUEST}" == "false" ]]; then
     export CI_PULL_REQUEST_BOOLEAN="false"
elif [[ "${TRAVIS_PULL_REQUEST}" =~ ^-?[0-9]+$ ]]; then
     export CI_PULL_REQUEST_BOOLEAN="true"
else
     printf "Unable to determine pull request status."
fi


# CI_PULL_REQUEST_NUMBER
if [[ "${TRAVIS_PULL_REQUEST}" == "false" ]]; then
     export CI_PULL_REQUEST_NUMBER="N/A"
elif [[ "${TRAVIS_PULL_REQUEST}" =~ ^-?[0-9]+$ ]]; then
     export CI_PULL_REQUEST_NUMBER="${APPVEYOR_PULL_REQUEST_NUMBER}"
else
     printf "Unable to determine pull request number."
fi


# 
export CI_SECURE_ENVIRONMENT_VARIABLE_TEST_BOOLEAN="${TRAVIS_SECURE_ENV_VARS}"


# 
export CI_REPOSITORY_NAME="${TRAVIS_REPO_SLUG}"


# 
export CI_HOST_OS_NAME="${TRAVIS_OS_NAME}"


# 
export CI_TAG="${TRAVIS_TAG}"


# 
export CI_REPOSITORY_PUSH_AUTHOR="Travis"


# 
export CI_REPOSITORY_PUSH_EMAIL="travis@travis.com"


# ${BUILD_OS} is supplied by the YAML file.
export CI_BIULD_OS="{BUILD_OS}"

# Temporary variable
export CI_PULL_REQUEST_BOOLEAN_ALLOWED="\"true\" \"false\" \"no data\""




