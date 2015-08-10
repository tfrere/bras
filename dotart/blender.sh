#!/n/bash

URL=http://api.art.rmngp.fr:80/v1/works/
API_KEY=demo
MP_ID=138772

if [ $# > 0 ]

	then
		MP_ID=$1
		rm -f /render/*.stl
		rm -f /render/*.gcode
		rm -f /render/*.jpg
		echo " ============= Recieve datas ============= "
		SIZE="$(curl -H "ApiKey: $API_KEY" "http://api.art.rmngp.fr:80/v1/works/$MP_ID" | jq ".hits.hits[0]._source.width,.hits.hits[0]._source.height")"
		COURANT="$(curl -H "ApiKey: $API_KEY" "http://api.art.rmngp.fr:80/v1/works/$MP_ID" | jq ".aggregations.periods.buckets[].key")"
		TECH="$(curl -H "ApiKey: $API_KEY" "http://api.art.rmngp.fr:80/v1/works/$MP_ID" | jq ".aggregations.techniques.buckets[].key")"
		IMG_URL="$(curl -H "ApiKey: $API_KEY" "http://api.art.rmngp.fr:80/v1/works/$MP_ID" | jq ".hits.hits[0]._source.images[0].urls.large.url")"

		wget -O "render/image.jpg" "$IMG_URL"

		echo $SIZE 
		echo $COURANT
		echo $TECH

		echo " ============= Blender process ============= "
		blender -b render/defaultScene.blend -P script.py -- "$COURANT" "$TECH" $SIZE

		echo " ============= Info Mesh ============= "
		./Slic3r/bin/slic3r --info render/defaultScene-Cube.stl
		
		echo " ============= Create final  ============= "
		./Slic3r/bin/slic3r render/defaultScene-Cube.stl --layer-height 0.2 --print-center 40,40

	else
		echo "Using default "

fi

