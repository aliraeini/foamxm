# Run on other openfoams before syncing here
cass=`find . | grep -F .H`
for cas in $cass; do
	echo '/------------/{N;N;/Class .* Declaration/d}' $cas
	sed -i '/------------/{N;N;/Class .* Declaration/d}' $cas
done
