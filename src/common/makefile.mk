local_dir    :=src/common
local_module := $(notdir $(local_dir))
local_src    :=$(addprefix $(local_dir)/,$(addsuffix .c,$(local_module)))

src          +=$(local_src)

