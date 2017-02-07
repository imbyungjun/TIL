#Maven

##1. Install
1 ) Download apache-maven-2.2.1-bin.zip from [http://maven.apache.org/download.html]  

2 ) Unzip and setup PATH variable
```
set MAVEN_HOME
add MAVEN_HOME to PATH
```
##2. Create a maven project
Create a maven project using archetype

```
$ mvn archetype:generate -DgroupId=com.nts -DartifactId=hello -DarchetypeArtifactId=maven-archetype-quickstart -DinteractiveMode=false
```

The project above command created will have directory hierarchy like this  

```
hello - src - main - java - com - nts
            - test - java - com - nts

```
Default source directory is 'src/main/java' and default test source directory is 'src/test/java'.  
GroupId will be the default package under each source directory.

(In general, *GroupId* is project domain and *artifactId* is prject name.)


##3. Maven basic commands
```
$ mvn [option] [<goal(s)>] [<phase(s)>]
```

example)
```
 # Execute clean and test phase
 $ mvn clean test

 # Execute clean phase and compile goal in compiler plugin
 $ mvn clean compiler:compile

 # Execute test phase without unit test
 $ mvn -Dmaven.test.skip=true test
```

##4. Create war project
Get list of archetypes that maven offers by default.

```
$ mvn archetype:generate -DarchetypeCatalog=internal
```

To create a web application project, select `maven-archetype-webapp`.

##5. Maven setting file

