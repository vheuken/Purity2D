




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
     Set-Variable `
         -Name "CI_HOST" `
         -Value "appveyor"
}
else
{
     Write-Host "Unable to determine CI host."
}

# 
Set-Variable `
     -Name "CI_API_URL" `
     -Value "${Env:APPVEYOR_API_URL}"


# 
Set-Variable `
     -Name "CI_PROJECT_ID" `
     -Value "${Env:APPVEYOR_PROJECT_ID}"


# 
Set-Variable `
     -Name "CI_PROJECT_NAME" `
     -Value "${Env:APPVEYOR_PROJECT_NAME}"


# 
Set-Variable `
     -Name "CI_PROJECT_SLUG" `
     -Value "${Env:APPVEYOR_PROJECT_SLUG}"


# 
Set-Variable `
     -Name "CI_BUILD_DIRECTORY" `
     -Value "${Env:APPVEYOR_BUILD_FOLDER}"


# 
Set-Variable `
     -Name "CI_BIULD_ID" `
     -Value "${Env:APPVEYOR_BUILD_ID}"


# 
Set-Variable `
     -Name "CI_BUILD_NUMBER" `
     -Value "${Env:APPVEYOR_BUILD_NUMBER}"


# 
Set-Variable `
     -Name "CI_BUILD_VERSION" `
     -Value "${Env:APPVEYOR_BUILD_VERSION}"


# CI_PULL_REQUEST_BOOLEAN
if ( "${Env:APPVEYOR_PULL_REQUEST_NUMBER}" -eq "" )
{
     Set-Variable `
         -Name "CI_PULL_REQUEST_BOOLEAN" `
         -Value "false"
}
elseif ( "${Env:APPVEYOR_PULL_REQUEST_NUMBER}" -match "(^\d+$)" )
{
     Set-Variable `
         -Name "CI_PULL_REQUEST_BOOLEAN" `
         -Value "true"
}
else
{
     Write-Host "Unable to determine pull request status."
     Set-Variable `
         -Name "CI_PULL_REQUEST_BOOLEAN" `
         -Value "no data"
}


# CI_PULL_REQUEST_NUMBER
if ( "${Env:APPVEYOR_PULL_REQUEST_NUMBER}" -eq "" )
{
     Set-Variable `
         -Name "CI_PULL_REQUEST_NUMBER" `
         -Value "N/A"
}
elseif ( "${Env:APPVEYOR_PULL_REQUEST_NUMBER}" -match "(^\d+$)" )
{
     Set-Variable `
         -Name "CI_PULL_REQUEST_NUMBER" `
         -Value "${Env:APPVEYOR_PULL_REQUEST_NUMBER}"
}
else
{
     Write-Host "Unable to determine pull request number."
     Set-Variable `
         -Name "CI_PULL_REQUEST_NUMBER" `
         -Value "no data"
}


# 
Set-Variable `
     -Name "CI_PULL_REQUEST_TITLE" `
     -Value "${Env:APPVEYOR_PULL_REQUEST_TITLE}"


# 
Set-Variable `
     -Name "CI_JOB_ID" `
     -Value "${Env:APPVEYOR_JOB_ID}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PROVIDER" `
     -Value "${Env:APPVEYOR_REPO_PROVIDER}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_SCM" `
     -Value "${Env:APPVEYOR_REPO_SCM}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_NAME" `
     -Value "${Env:APPVEYOR_REPO_NAME}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_BRANCH" `
     -Value "${Env:APPVEYOR_REPO_BRANCH}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PULL_ID" `
     -Value "${Env:APPVEYOR_REPO_COMMIT}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PULL_AUTHOR" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_AUTHOR}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PULL_EMAIL" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_AUTHOR_EMAIL}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PULL_TIMESTAMP" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_TIMESTAMP}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PULL_MESSAGE_SHORT" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_MESSAGE}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PULL_MESSAGE_FULL" `
     -Value "${Env:APPVEYOR_REPO_COMMIT_MESSAGE_EXTENDED}"


# 
Set-Variable `
     -Name "CI_BUILD_SCHEDULE_BOOLEAN" `
     -Value "${Env:APPVEYOR_SCHEDULED_BUILD}"


# 
Set-Variable `
     -Name "CI_BUILD_COMPILER_PLATFORM" `
     -Value "${Env:PLATFORM}"


# 
Set-Variable `
     -Name "CI_BUILD_COMPILER_CONFIGURATION" `
     -Value "${Env:CONFIGURATION}"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PUSH_AUTHOR" `
     -Value "AppVeyor"


# 
Set-Variable `
     -Name "CI_REPOSITORY_PUSH_EMAIL" `
     -Value "appveyor@appveyor.com"


# ${BUILD_OS} is supplied by the YAML file.
Set-Variable `
     -Name "CI_BUILD_OS" `
     -Value "${BUILD_OS}"


# Temporary variable
Set-Variable `
     -Name "CI_PULL_REQUEST_BOOLEAN_ALLOWED" `
     -Value "${`"true`" `"false`" `"no data`"}"


"${CI_HOST}"
"${CI_API_URL}"
"${CI_PROJECT_ID}"
"${CI_PROJECT_NAME}"
"${CI_PROJECT_SLUG}"
"${CI_BUILD_DIRECTORY}"
"${CI_BIULD_ID}"
"${CI_BUILD_NUMBER}"
"${CI_BUILD_VERSION}"
"${CI_PULL_REQUEST_BOOLEAN}"
"${CI_PULL_REQUEST_NUMBER}"
"${CI_PULL_REQUEST_TITLE}"
"${CI_JOB_ID}"
"${CI_REPOSITORY_PROVIDER}"
"${CI_REPOSITORY_SCM}"
"${CI_REPOSITORY_NAME}"
"${CI_REPOSITORY_BRANCH}"
"${CI_REPOSITORY_PULL_ID}"
"${CI_REPOSITORY_PULL_AUTHOR}"
"${CI_REPOSITORY_PULL_EMAIL}"
"${CI_REPOSITORY_PULL_TIMESTAMP}"
"${CI_REPOSITORY_PULL_MESSAGE_SHORT}"
"${CI_REPOSITORY_PULL_MESSAGE_FULL}"
"${CI_BUILD_SCHEDULE_BOOLEAN}"
"${CI_BUILD_COMPILER_PLATFORM}"
"${CI_BUILD_COMPILER_CONFIGURATION}"
"${CI_REPOSITORY_PUSH_AUTHOR}"
"${CI_REPOSITORY_PUSH_EMAIL}"
"${CI_BUILD_OS}"
"${CI_PULL_REQUEST_BOOLEAN_ALLOWED}"

















