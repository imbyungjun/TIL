filename=`basename $1`
echo "<script>
	location.href=\"$1\";
</script>" > $filename.link
