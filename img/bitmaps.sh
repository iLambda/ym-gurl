# Convert all files 
for in in src/*.png;
do
    # Get base name and output target name 
    base="$(basename -- $in)";
    out="fixtures/${base/%png/xbm}";
    # Convert 
    convert ./"$in" XBM:"$out";
    # Say
    echo "Successfully ${in} to ${out}";
done

# Remove bitmaps.h
rm -rf ./bitmaps.

# Rewrite in files 
prefix="IMG"
sed -i 's/static char/const unsigned char/g' ./fixtures/*
sed -i -r "s/^#define ([a-zA-Z0-9_]*)/#define ${prefix}_\U\1/g" ./fixtures/*
sed -i -r "s/([a-zA-Z0-9_]*)\[\]/${prefix}_\U\1[]/g" ./fixtures/*
sed -i -r "s/_BITS/_DATA/g" ./fixtures/*

# Add define for all
for in in fixtures/*.xbm;
do
    # Get include name
    widthname=$(grep '_WIDTH' ${in} | head -1);
    identifier=$(echo ${widthname} | sed -r "s/#define//g" | sed -r "s/ *[0-9]*//g" | sed -r "s/_WIDTH//g");
    # Make macro
    macro="#define ${identifier} ${identifier}_WIDTH, ${identifier}_HEIGHT, img::${identifier}_DATA"
    # Append macro to end
    echo $macro >> ${in};
    echo $identifier
done

# OK
echo "Rewrite in .xbm files OK"

# Make script header and end
inc_guard="#ifndef __YM_GURL_IMG_BITMAPS
#define __YM_GURL_IMG_BITMAPS"
inc_begin="namespace img {"
inc_mid=""
# Include all the files
for xbm in fixtures/*.xbm;
do
    # Make include 
    include=$(printf "    #include \"%s\"\n" "${xbm}");
    # Append
    inc_mid=$(printf "%s\n%s" "${inc_mid}" "${include}");
done
# Print it to file 
printf "%s\n\n%s%s\n}\n#endif\n" "${inc_guard}" "${inc_begin}" "${inc_mid}" > bitmaps.h
# Log
echo "File bitmaps.h successfully generated"