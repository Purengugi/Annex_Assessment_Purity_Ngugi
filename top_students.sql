-- retrieve top 3 students by score, break ties by ID ascending
SELECT   ID,
         NAME
FROM     STUDENT
ORDER BY SCORE DESC,
         ID    ASC
LIMIT    3;
