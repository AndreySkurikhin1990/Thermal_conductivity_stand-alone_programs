function tm = tmp31()
x = [0.0, .1488743389, .4333953941, .6794095682, .8650633666, .9739065285]'
y = [0.0, 1503.32158713938, 2004.78303570275, 2495.09250579963, ...
    3044.62899329486, 3709.12502109211, 4567.40650306271, 5762.97273448694, ...
    7613.99482631694, 11045.6325211325, 20764.7554806188]'
n=length(x);
f=0;
for k=2:n
    f(k) = bbfn(x(k));
end
f=1*f'
n=length(y);
f=0;
for k=2:n
    f(k) = bbfn(y(k));
end
f=1*f'
tm=0;
end