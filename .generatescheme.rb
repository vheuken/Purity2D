require 'xcodeproj'
xcproj = Xcodeproj::Project.open("Purity2D.xcodeproj")
xcproj.recreate_user_schemes
xcproj.save
