local_dir :=src
local_src :=$(addprefix $(local_dir)/,main.c)

src       +=$(local_src)

