local_dir    :=src/lock
local_module :=$(notdir $(local_dir))
local_src    :=$(addprefix $(local_dir)/,$(addsuffix .c,$(local_module)))

src          +=$(local_src)

