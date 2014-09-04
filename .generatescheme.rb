require 'xcodeproj'
xcproj = Xcodeproj::Project.open("Purity-Engine.xcodeproj")
xcproj.recreate_user_schemes
xcproj.save
