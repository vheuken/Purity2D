# Modified script originally from http://sleepycoders.blogspot.com/2013/03/sharing-travis-ci-generated-files.html
# Currently makes the following assumptions:
         # The Appveyor YML file has the secure variable ${GH_TOKEN} to connect to Github
         # All desired files are located in ${TRAVIS_BUILD_DIR}/release/
printf "${APPVEYOR_PULL_REQUEST_NUMBER}"

if [ "${APPVEYOR_PULL_REQUEST_NUMBER}" == "false" ]; then
         printf "Starting gh-pages update\n"
         
         printf "Setting up Git\n"
         cd ${APPVEYOR_BUILD_FOLDER}
         test ! -d ./Git \
                 && mkdir ./Git \
                 && cd ./Git
         git config --global user.email "appveyor@appveyor.com"
         git config --global user.name "Appveyor"
         
         printf "Connecting to gh-pages\n"
         git clone \
                 --quiet \
                 --branch=gh-pages \
                         https://${GH_TOKEN}@github.com/${APPVEYOR_PROJECT_SLUG} \
                 gh-pages > /dev/null
         
         printf "Copying new files\n"
         cd ./gh-pages
         test ! -d ./${APPVEYOR_REPO_BRANCH}/${BUILD_OS} \
                 && mkdir -p ./${APPVEYOR_REPO_BRANCH}/${BUILD_OS}
         cp -Rf ${APPVEYOR_BUILD_FOLDER}/release/* ./${APPVEYOR_REPO_BRANCH}/${BUILD_OS}
         
         printf "Committing and pushing files\n"
         git add -f .
         git commit -m "Appveyor build ${APPVEYOR_BUILD_NUMBER} pushed to gh-pages"
         git push -fq origin gh-pages > /dev/null
         
         printf "Done\n"
fi
