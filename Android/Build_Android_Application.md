#Run Gradle from the Command Line
###Building in Debug Mode
```
$ chmod +x gradlew
$ ./gradlew assembleDebug
```

###Building in Release Mode
####1. Build unsigned
```
$ ./gradlew assembleRelease
```

####2. Build signed and aligned
To specify your keystore and alias, open the module build.gradle file (found in the root of the module directory) and add entries for `storeFile`, `storePassword`, `keyAlias` and `keyPassword`. For example:

```
storeFile file("myreleasekey.keystore")
keyAlias "MyReleaseKey"
```

Save your changes. Now you can build a signed .apk in release mode:

1. Open a command-line and navigate to the root of your module directory.
2. Edit the build.gradle file to build your project in release mode:

	```
	...
	android {
		...
		defaultConfig { ... }
    	signingConfigs {
        	release {
            	storeFile file("myreleasekey.keystore")
	            storePassword "password"
    	        keyAlias "MyReleaseKey"
        	    keyPassword "password"
	        }
    	}
	    buildTypes {
    	    release {
        	    ...
            	signingConfig signingConfigs.release
	        }
    	}
	}
	...
	```
3. When prompted, enter you keystore and alias passwords.