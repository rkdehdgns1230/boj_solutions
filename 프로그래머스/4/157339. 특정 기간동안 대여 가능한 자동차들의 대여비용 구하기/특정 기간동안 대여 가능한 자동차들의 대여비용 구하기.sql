# CRCC와 CRDP 이용해서 차량에 맞는 30일 요금을 계산
# WHERE 절에서 내부 statement 활용해 빌릴 수 있는 차량 정보 획득 CAR_RENTAL_COMPANY_RENTAL_HISTORY 사용

SELECT CRCC.CAR_ID, CRCC.CAR_TYPE, ROUND(CRCC.DAILY_FEE * 30 * (1 - (CRCDP.DISCOUNT_RATE / 100))) as FEE
FROM CAR_RENTAL_COMPANY_CAR as CRCC JOIN CAR_RENTAL_COMPANY_DISCOUNT_PLAN as CRCDP ON CRCC.CAR_TYPE = CRCDP.CAR_TYPE and CRCDP.DURATION_TYPE LIKE '30%'
WHERE CRCC.CAR_ID not in (
    SELECT CAR_ID
    FROM CAR_RENTAL_COMPANY_RENTAL_HISTORY
    WHERE START_DATE <= '2022-11-30' AND END_DATE >= '2022-11-01'
) # 11월 30일 이전에 대여하거나, 11월 1일 이전에 반납하는 차량 정보
and CRCC.CAR_TYPE in ('SUV', '세단')
and CRCC.DAILY_FEE * 30 * (1 - (CRCDP.DISCOUNT_RATE / 100)) BETWEEN 500000 AND 2000000
ORDER BY FEE DESC, CAR_TYPE ASC, CAR_ID DESC;