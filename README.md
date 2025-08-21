**Bối cảnh thực tế và nhu cầu của đề tài**

Hiện nay, việc giám sát nhiệt độ là nhu cầu quan trọng trong nhiều lĩnh vực như gia đình, công nghiệp và y tế nhằm đảm bảo an toàn và hiệu quả hoạt động. Tuy nhiên, các giải pháp hiện tại thường phức tạp và chi phí cao. Một hệ thống đơn giản, sử dụng cảm biến nhiệt độ để theo dõi, hiển thị trạng thái qua đèn và cảnh báo khi nhiệt độ cao sẽ giải quyết vấn đề này hiệu quả.


Vi điều khiển, như STM32, cho phép tích hợp nhiều chức năng trên một chip: đo nhiệt độ chính xác, điều khiển đèn LED, hiển thị dữ liệu qua LCD và xử lý cảnh báo. Điều này giúp hệ thống trở nên linh hoạt, chi phí thấp và dễ triển khai trong nhiều ứng dụng thực tế.

<img width="638" height="546" alt="image" src="https://github.com/user-attachments/assets/528a7b8d-d796-4b9e-bc10-2e4b0a6c9854" />

**Thiết kế chi tiết**

<img width="684" height="479" alt="image" src="https://github.com/user-attachments/assets/fad0addd-9b6f-47bb-a708-cf483d50b68d" />
•	Các thành phần chính: 

o	Vi điều khiển STM32F103C8: Trung tâm điều khiển.

o	Cảm biến nhiệt độ LM35: Đo nhiệt độ.

o	Mạch giao tiếp UART với máy tính: Kết nối để truyền nhận dữ liệu.

o	Mạch hiển thị LCD 16x2: Hiển thị thông tin nhiệt độ.

o	Mạch điều khiển quạt (qua relay): Điều chỉnh trạng thái quạt.

o	LED và các nút nhấn: Hiển thị trạng thái và cho phép điều khiển hệ thống.



1.	Nguồn cấp cho mạch:
o	Nguồn 3.3V: Cung cấp cho vi điều khiển STM32, LCD, và các linh kiện khác như LM35. 
	Được ổn áp từ IC nguồn (như 790 hoặc tương tự).
o	Nguồn 12V: Cấp cho quạt và relay.
2.	Mạch điều khiển relay (quạt):
o	Relay RL1 được điều khiển qua GPIO của STM32. Khi nhiệt độ vượt ngưỡng, STM32 kích hoạt relay để bật quạt.
o	Diode D6 bảo vệ mạch khi relay hoạt động, chống lại xung điện ngược.
3.	Mạch giao tiếp UART:
o	Kết nối vi điều khiển với cổng COM qua TX và RX để gửi/nhận dữ liệu. Điều này giúp giao tiếp với máy tính hoặc các thiết bị khác.
4.	Mạch LED báo trạng thái:
o	LED xanh nhấp nháy (D1): Đèn hiển thị hệ thống chạy.
o	LED đỏ (D2, D3, D4,D5): Cảnh báo khi nhiệt độ vượt ngưỡng.Nếu đèn 1 nhiệt độ >16, đèn 2 nhiệt độ > 32, đèn 3 nhiệt độ >48 ,đèn 4 nhiệt độ >64 sáng
o	LED nhấp nháy (D2, D3, D4,D5): Nếu nhiệt độ > 80. Thông báo cảnh báo nghiêm trọng.
5.	Mạch hiển thị LCD:
o	Hiển thị thông tin nhiệt độ, thông báo cảnh báo.
o	Kết nối qua giao thức 4-bit (D4–D7) với vi điều khiển để giảm số chân giao tiếp.
6.	Mạch xử lý tín hiệu từ LM35:
o	Đầu ra tín hiệu từ cảm biến LM35 (tỷ lệ với nhiệt độ) được đưa vào chân ADC của STM32 để chuyển đổi tín hiệu từ tương tự sang số.
7.	Nút nhấn Start/Stop:
o	Nút Start khởi động hệ thống giám sát.
o	Nút Stop dừng toàn bộ hệ thống.

