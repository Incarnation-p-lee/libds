define heap
set $t1=$arg0->alias->size
p $t1
set $t2=1
while ($t2 <= $t1)
p *$arg0->alias->base[$t2]
set $t2=$t2+1
end
end
