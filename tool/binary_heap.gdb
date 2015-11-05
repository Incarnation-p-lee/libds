define line
set $tmp=$arg0
while($tmp < $arg0 * 2)
p heap->base[$tmp].nice
set $tmp=$tmp+1
end
end
