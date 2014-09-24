printf "Testing inbuilt environment variable\n"
printf "${CI}\n"


printf "\n"


printf "Testing set variables\n"

printf "${CI_HOST}\n"
printf "${CI_HAS_JOSH_K_SEAL_OF_APPROVAL}\n"
printf "${CI_REPOSITORY_BRANCH}\n"
printf "${CI_BUILD_DIRECTORY}\n"
printf "${CI_BIULD_ID}\n"
printf "${CI_BUILD_NUMBER}\n"
printf "${CI_REPOSITORY_PULL_ID}\n"
printf "${CI_REPOSITORY_PULL_RANGE}\n"
printf "${CI_JOB_ID}\n"
printf "${CI_JOB_NUMBER}\n"
printf "${CI_PULL_REQUEST_BOOLEAN}\n"
printf "${CI_PULL_REQUEST_NUMBER}\n"
printf "${CI_SECURE_ENVIRONMENT_VARIABLE_TEST_BOOLEAN}\n"
printf "${CI_REPOSITORY_NAME}\n"
printf "${CI_HOST_OS_NAME}\n"
printf "${CI_TAG}\n"
printf "${CI_REPOSITORY_PUSH_AUTHOR}\n"
printf "${CI_REPOSITORY_PUSH_EMAIL}\n"
printf "${CI_BIULD_OS}\n"
printf "${CI_PULL_REQUEST_BOOLEAN_ALLOWED}\n"

printf "Done\n"
exit 0

