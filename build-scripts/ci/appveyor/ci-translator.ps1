# See if this is a CI environment.
# Appveyor has CI set to "true"
if ( "${Env:CI}" -eq "true" )
{
     Write-Host "This is a continuous integration environment."
}
else
{
     Write-Host "This is not a continuous integration environment."
}


# CI_HOST
if ( "${Env:APPVEYOR}" -eq "true" )
{
     Set-Item `
         -Path "Env:CI_HOST" `
         -Value "appveyor"
}
else
{
     Write-Host "Unable to determine CI host."
}

# 
Set-Item `
     -Path "Env:CI_API_URL" `
     -Value "${Env:APPVEYOR_API_URL}"


# 
Set-Item `
     -Path "Env:CI_PROJECT_ID" `
     -Value "${Env:APPVEYOR_PROJECT_ID}"


# 
Set-Item `
     -Path "Env:CI_PROJECT_NAME" `
     -Value "${Env:APPVEYOR_PROJECT_NAME}"


# 
Set-Item `
     -Path "Env:CI_PROJECT_SLUG" `
     -Value "${Env:APPVEYOR_PROJECT_SLUG}"


# 
Set-Item `
     -Path "Env:CI_BUILD_DIRECTORY" `
     -Value "${Env:APPVEYOR_BUILD_FOLDER}"


# 
Set-Item `
     -Path "Env:CI_BIULD_ID" `
     -Value "${Env:APPVEYOR_BUILD_ID}"


# 
Set-Item `
     -Path "Env:CI_BUILD_NUMBER" `
     -Value "${Env:APPVEYOR_BUILD_NUMBER}"


# 
Set-Item `
     -Path "Env:CI_BUILD_VERSION" `
     -Value "${Env:APPVEYOR_BUILD_VERSION}"


# CI_PULL_REQUEST_BOOLEAN
if ( "${Env:APPVEYOR_PULL_REQUEST_NUMBER}" -eq "" )
{
     Set-Item `
         -Path "Env:CI_PULL_REQUEST_BOOLEAN" `
         -Value "false"
}
elseif ( "${Env:APPVEYOR_PULL_REQUEST_NUMBER}" -match "(^\d+$)" )
{
     Set-Item `
         -Path "Env:CI_PULL_REQUEST_BOOLEAN" `
         -Value "true"
}
else
{
     Write-Host "Unable to determine pull request status."
     Set-Item `
         -Path "Env:CI_PULL_REQUEST_BOOLEAN" `
         -Value "no data"
}


# CI_PULL_REQUEST_NUMBER
if ( "${Env:APPVEYOR_PULL_REQUEST_NUMBER}" -eq "" )
{
     Set-Item `
         -Path "Env:CI_PULL_REQUEST_NUMBER" `
         -Value "N/A"
}
elseif ( "${Env:APPVEYOR_PULL_REQUEST_NUMBER}" -match "(^\d+$)" )
{
     Set-Item `
         -Path "Env:CI_PULL_REQUEST_NUMBER" `
         -Value "${Env:APPVEYOR_PULL_REQUEST_NUMBER}"
}
else
{
     Write-Host "Unable to determine pull request number."
     Set-Item `
         -Path "Env:CI_PULL_REQUEST_NUMBER" `
         -Value "no data"
}


# 
Set-Item `
     -Path "Env:CI_PULL_REQUEST_TITLE" `
     -Value "${Env:APPVEYOR_PULL_REQUEST_TITLE}"


# 
Set-Item `
     -Path "Env:CI_JOB_ID" `
     -Value "${Env:APPVEYOR_JOB_ID}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PROVIDER" `
     -Value "${Env:APPVEYOR_REPO_PROVIDER}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_SCM" `
     -Value "${Env:APPVEYOR_REPO_SCM}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_NAME" `
     -Value "${Env:APPVEYOR_REPO_NAME}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_BRANCH" `
     -Value "${Env:APPVEYOR_REPO_BRANCH}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PULL_ID" `
     -Value "${Env:APPVEYOR_REPO_COMMIT}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PULL_AUTHOR" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_AUTHOR}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PULL_EMAIL" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_AUTHOR_EMAIL}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PULL_TIMESTAMP" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_TIMESTAMP}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PULL_MESSAGE_SHORT" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_MESSAGE}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PULL_MESSAGE_FULL" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_MESSAGE_EXTENDED}"


# 
Set-Item `
     -Path "Env:CI_BUILD_SCHEDULE_BOOLEAN" `
     -Value "${Env:APPVEYOR_SCHEDULED_BUILD}"


# 
Set-Item `
     -Path "Env:CI_BUILD_COMPILER_PLATFORM" `
     -Value "${Env:PLATFORM}"


# 
Set-Item `
     -Path "Env:CI_BUILD_COMPILER_CONFIGURATION" `
     -Value "${Env:CONFIGURATION}"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PUSH_AUTHOR" `
     -Value "AppVeyor"


# 
Set-Item `
     -Path "Env:CI_REPOSITORY_PUSH_EMAIL" `
     -Value "appveyor@appveyor.com"


# ${BUILD_OS} is supplied by the YAML file.
Set-Item `
     -Path "Env:CI_BUILD_OS" `
     -Value "${Env:BUILD_OS}"


# Temporary variable
Set-Item `
     -Path "Env:CI_PULL_REQUEST_BOOLEAN_ALLOWED" `
     -Value "${`"true`" `"false`" `"no data`"}"




