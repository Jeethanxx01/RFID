TARGETS := zone_infos.cpp zone_infos.h zone_policies.cpp zone_policies.h

TOOLS := $(abspath ../../../../AceTimeTools)

TZ_VERSION := 2022b
START_YEAR := 2000
UNTIL_YEAR := 2050

all:
	$(TOOLS)/tzcompiler.sh \
		--tag $(TZ_VERSION) \
		--action zonedb \
		--language arduino \
		--scope extended \
		--start_year $(START_YEAR) \
		--until_year $(UNTIL_YEAR)

zonedb.json:
	$(TOOLS)/tzcompiler.sh \
		--tag $(TZ_VERSION) \
		--action zonedb \
		--language json \
		--scope extended \
		--start_year $(START_YEAR) \
		--until_year $(UNTIL_YEAR)
