#!/usr/bin/env bash
# Requires Bash minimum version 3.1.0


if printf  "${CI_PULL_REQUEST_BOOLEAN_ALLOWED}" | grep -E "\"${CI_PULL_REQUEST_BOOLEAN}\"" > /dev/null; then
    if [ "${CI_PULL_REQUEST_BOOLEAN}" == "true" ]; then
         printf "Pull request\n"
         exit 0
    elif [ "${CI_PULL_REQUEST_BOOLEAN}" == "false" ]; then
         printf "Starting gh-pages update\n"
         
         printf "Setting up Git\n"
         cd ${CI_BUILD_DIRECTORY}
         test ! -d ./Git \
             && mkdir ./Git \
             && cd ./Git
         git config --global user.email "${CI_REPOSITORY_PUSH_EMAIL}"
         git config --global user.name "${CI_REPOSITORY_PUSH_AUTHOR}"
         
         printf "Connecting to gh-pages\n"
         git clone \
         --quiet \
         --branch=gh-pages \
             https://${GH_TOKEN}@github.com/${CI_REPOSITORY_NAME} \
         gh-pages > /dev/null
         
         printf "Copying new files\n"
         cd ./gh-pages
         test ! -d ./${CI_REPOSITORY_BRANCH}/${CI_BUILD_OS} \
             && mkdir -p ./${CI_REPOSITORY_BRANCH}/${CI_BUILD_OS}
         cp -Rf "${CI_BUILD_DIRECTORY}/release/test.txt" "./${CI_REPOSITORY_BRANCH}/${CI_BUILD_OS}"
         
         printf "Committing and pushing files\n"
         git add -f .
         git commit -m "Build \"${CI_HOST}-${CI_BUILD_NUMBER}\""
         git push -fq origin gh-pages > /dev/null
         
         printf "Done\n"
         exit 0
    elif [ "${CI_PULL_REQUEST_BOOLEAN}" == "no data" ]; then
         printf "Warning: Unable to determine pull request status\n"
         exit 0
    else
         printf "Error: Variable \${CI_PULL_REQUEST_BOOLEAN} returned \"${CI_PULL_REQUEST_BOOLEAN}\". Expected values: \"true\" \"false\" \"no data\". This script is unprepared to handle \"${CI_PULL_REQUEST_BOOLEAN}\" but has determined that \"${CI_PULL_REQUEST_BOOLEAN}\" is an allowed value.\n"
         exit 1
    fi
elif [ -n "${CI_PULL_REQUEST_BOOLEAN}" ]; then
     printf "Error: Variable \${CI_PULL_REQUEST_BOOLEAN} returned \"${CI_PULL_REQUEST_BOOLEAN}\". Expected values: ${CI_PULL_REQUEST_BOOLEAN_ALLOWED}.\n"
     exit 1
else
     printf "Error: Variable \${CI_PULL_REQUEST_BOOLEAN} not set.\n"
     exit 1
fi



