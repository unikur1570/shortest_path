wget https://download.geofabrik.de/europe/belarus-latest.osm.pbf

# extract Belarus
osmium cat belarus-latest.osm.pbf -o belarus.osm 
# get Minsk boundaries
osmium getid -r -t belarus-latest.osm.pbf r59195 -o minsk-boundary.osm

### for Minsk ###
# extract Minsk from Belarus
osmium extract --polygon minsk-boundary.osm belarus-latest.osm.pbf -o minsk.osm

# filter Minsk.osm file with tags roads for only cars
osmium tags-filter minsk.osm w/highway="motorway" w/highway="motorway_link" w/highway="trunk" w/highway="trunk_link" w/highway="primary" w/highway="primary_link" w/highway="secondary" w/highway="secondary_link" w/highway="tertiary" w/highway="tertiary_link" w/highway="unclassified" w/highway="unclassified_link" w/highway="residential" w/highway="residential_link" w/highway="service" w/highway="service_link" w/highway="living_street" w/highway="track" -o filtered_minsk.osm
