# Calender
## **行事曆**

### **執行流程**
>未曾使用過則寫一新檔案  
>>輸入日期及事項
>>>存入檔案
>>>>讀取後輸出
>>>>回到輸入事項

>使用過則直接輸出紀錄，後輸入事項  


   






---
函數                                             | 參數          | 執行        | 呼叫
---- | ---- | ---- | ----
calendar::calendar()                            | 建構函數       | 抓取當天時間  | -  
calendar::window(int[], int[])                  | 任務日期       | 輸出畫面     | nextmonth(int*, int*, int*,int)  
calendar::newtask(tm*)	                        | 當天時間       | 輸入事項內容  | recall(), save(int, int, char[], char[], char[])
calendar::recall()                              | _             | 讀取記錄檔案  | window(int[], int[])  
calendar::save(int, int, char[], char[], char[])| 任務日期、內容  | 存入記錄檔案  | _ 
calendar::nextmonth(int*, int*, int*,int)       | _             | 調整月份推進  |_

