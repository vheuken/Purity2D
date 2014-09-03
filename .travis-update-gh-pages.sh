#Modified script originally from http://sleepycoders.blogspot.com/2013/03/sharing-travis-ci-generated-files.html
if [ "${TRAVIS_PULL_REQUEST}" == "false" ]; then
         printf "Starting gh-pages update\n"
         
         printf "Setting up Git\n"
         cd ${TRAVIS_BUILD_DIR}
         mkdir Git && cd Git
         git config --global user.email "travis@travis-ci.org"
         git config --global user.name "Travis"
         
         printf "Connecting to gh-pages\n"
         git clone --quiet --branch=gh-pages https://${GH_TOKEN}@github.com/${TRAVIS_REPO_SLUG}  gh-pages > /dev/null
         
         printf "Copying new files\n"
         cd gh-pages
         test ! -d ${BUILD_OS} && mkdir ${BUILD_OS}
         cp -Rf ${TRAVIS_BUILD_DIR}/release/* ./${BUILD_OS}
         
         printf "Committing and pushing files\n"
         git add -f .
         git commit -m "Travis build ${TRAVIS_BUILD_NUMBER} pushed to gh-pages"
         git push -fq origin gh-pages > /dev/null
         
         printf "Done\n"
fi
