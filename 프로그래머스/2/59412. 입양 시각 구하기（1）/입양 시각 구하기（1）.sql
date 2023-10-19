SELECT EXTRACT(HOUR from DATETIME) as HOUR, COUNT(ANIMAL_ID) as COUNT
FROM ANIMAL_OUTS
group by EXTRACT(HOUR from DATETIME) having hour >= 9 and hour < 20
order by hour;