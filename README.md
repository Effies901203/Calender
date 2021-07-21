# Calender
## **行事曆**

### **執行流程**
>未曾使用過則寫一新檔案  

>否則直接進入下一步驟
>>輸入日期及事項
>>>存入檔案
>>>>讀取後輸出  

>>>>回到輸入事項

----
   


---
函數                                 | 參數      |     回傳類型 | 執行             | 呼叫
---- | ---- | ---- | ---- | ----
cCountry::cCountry()                | _            | 建構函數 | 設定第一人感染     | f()  
cCountry::f()                       | _            | Void    | 處理向量及決定座標 | _  
cCountry::RandomInfect()            | _            | Void    | 抓人感染         | InfectAnother(cHuman*, int), makep(double, double, double)  
cHuman::InfectAnother(cHuman*, int) | 第二人, 第幾天 | bool    | 以隨機決定是否感染 | _  
cCountry::Tomorrow()                | _            | Void    | 時間和參數變異推進 | muta(), Died(int)  
cHuman::Died(int)                   | 第幾天        | bool    | 決定是否死亡      | VirusLevel(int)  
cHuman::VirusLevel(int)             | 第幾天        | double  | 回傳病毒數值      | _  

