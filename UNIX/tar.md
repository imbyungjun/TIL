#Tar
GNU 'tar' saves many files together into a single tape or disk archive, and can restore individual files from the archive


####Usage:

```
Common options
	-v : Verbose 
	-f <file_name> : location of archive

Create: tar -c [options] [ file | directory | archive ]
	-z : compress archive with gzip.
	--exclude <pattern> : skip files that match pattern
	-C <dir>  Change to <dir> before processing remaining files
	
Extract: tar -x [options] [<patterns]
<patterns> If specified, extract only entries that match
	-k Keep existing files
	-m Don't restore modification times
	-O Write entries to stdout, dont' restore to disk
	-p Restore permissions
```

#Compress tar.gz

Example ) Compress all files in current directory to xxx.tar.gz

```
$ tar -cvzf xxx.tar.gz *
```
#Uncompress tar.gz

Example ) Uncompress and untar xxx.tar.gz

```
$ tar -zxvf xxx.tar.gz
```
Example ) Uncompress tar.gz into different directory

```
$ tar -zxvf xxx.tar.gz -C ../other/dir
```