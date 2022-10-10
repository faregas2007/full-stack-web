- option 1: build libmysqlclient seperated systemwide and access it via linkopts in cc_library 
			requires to find pacakge if exists in local/remote machine system.  
- option 2: built-in package with bazel itself. 
			requires to write rules in bazel to automatically installed the package. 

