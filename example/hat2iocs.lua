local math = require("math")

iocs.crtmod(4)
iocs.g_clr_on()
iocs.apage(0)
iocs.vpage(15)

local d = {}
for i = 1, 160 do
    d[i] = 100
end

local c = { 0, 3, 5, 7, 9, 11, 13, 15 }
local t0, t1, t2
local dr = math.pi / 180
local zzz = {}
local r

function draw_surface()
    local i = 1
    for y=-180, 180, 6 do
        for x=-180, 180, 4 do
            local z = zzz[i]
            local sx = 81 + x // 3 - y // 6
            local sy = 40 - y // 6 - z // 4

            if sx >= 1 and sx < 161 then
                if d[sx] > sy then
                    iocs.pset(sx * 3, sy * 4, c[math.floor((z + 100.0) * 0.035) + 2] or 0)
                    d[sx] = sy
                end
            end
            i=i+1
        end
    end
end

local i=1
print "START"
t0 = os.time()
for y=-180, 180, 6 do
    for x = -180, 180, 4 do
        if x == 0 and y == 0 then
            r = 0.0
        else
            r = dr * math.sqrt(x*x+y*y)
        end
        zzz[i] = 100.0 * math.cos(r) - 30.0 * math.cos(3.0 * r)
        i=i+1
    end
end

t1 = os.time()
print ("PART1 : " .. (t1-t0) )
draw_surface()
print( "END : " .. (os.time() - t0) )
