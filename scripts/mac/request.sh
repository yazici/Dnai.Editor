#!/bin/sh

#VARIABLES
baseURL='https://api.dnai.io/'
dmg_path="$TRAVIS_BUILD_DIR/"
dmg_name="DNAI-Installer.dmg"
slug="installer"
#END

release_version=null

if [ "$1" == "--release" ]
  then
    if [ "$2" ]
	then
	release_version=$2
    fi
fi

if [ $release_version == null ]
then
	echo "--- NO VERSION EXIT REQUEST ---"
    exit 1
fi

login=$DEPLOY_LOGIN
password=$DEPLOY_PASSWORD

brew install jq

res=$(curl -X POST "$baseURL"signin -H 'content-type: application/json' -d "{ \"login\": \"$login\", \"password\": \"$password\"}")
token=$(echo $res | jq -r '.token')

if [ $token == null ]
then
    echo "failed to get token"
    echo $res
    exit 2
fi

res=$(curl -X POST "$baseURL"download/softwares/mac -H "authorization: Bearer $token" -H 'content-type: application/json' -d "{
      \"title\": \"Revision for $release_version\",
      \"description\": \"Generated by installer.sh on Mac.\",
      \"slug\": \"$slug\",
      \"currentVersion\": \"$release_version\"
}")

echo $res

res=$(curl -X PATCH "$baseURL"download/softwares/mac/$slug -H "authorization: Bearer $token" -H 'content-type: application/json' -d "{
      \"title\": \"Revision for installer $slug\",
      \"description\": \"Generated by installer.sh on Mac.\",
      \"slug\": \"$slug\",
      \"currentVersion\": \"$release_version\"
}")

echo $res

#requete vers PUT MISSING THE FILE
pwd

res=$(curl -X PUT --upload-file "$dmg_path$dmg_name" "$baseURL"download/softwares/mac/$slug/$release_version -H "Authorization: Bearer $token" -H 'content-type: application/octet-stream')

echo $res

exit 0