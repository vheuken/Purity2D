if ( "${APPVEYOR_PULL_REQUEST_NUMBER}" -eq "false" ) {
         Write-Host "Starting gh-pages update"
         
         Write-Host "Setting up Git"
         Set-Location ${APPVEYOR_BUILD_FOLDER}
         New-Item ".\Git" `
                 -ItemType directory `
                 -Force
         Set-Location .\Git
         git config --global user.email "appveyor@appveyor.com"
         git config --global user.name "Appveyor"
         
         Write-Host "Connecting to gh-pages"
         git clone `
                 --quiet `
                 --branch=gh-pages `
                 https://${GH_TOKEN}@github.com/${APPVEYOR_PROJECT_SLUG} `
                 gh-pages > $null
         
         Write-Host "Copying new files"
          New-Item ".\${APPVEYOR_REPO_BRANCH}\${BUILD_OS}" `
                 -ItemType directory `
                 -Force
         Copy-Item `
                 -Path "${APPVEYOR_BUILD_FOLDER}\release\*" `
                 -Destination "./${APPVEYOR_REPO_BRANCH}/${BUILD_OS}" `
                 -Force `
                 -Recurse
         
         Write-Host "Committing and pushing files"
         git add -f .
         git commit -m "Appveyor build ${APPVEYOR_BUILD_NUMBER} pushed to gh-pages"
         git push -fq origin gh-pages > $null
         
         Write-Host "Done"
}



