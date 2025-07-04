using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using ZedGraph;// Thư viện để vẽ biểu đồ
using static System.Windows.Forms.LinkLabel;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
namespace BAI_CUOI_KI
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();// Khởi tạo giao diện form
        }
        // Mảng chứa các giá trị Baud rate và Port name
        string[] baud = { "1200", "2400", "4800", "9600", "115200" };
        string[] port = { "COM1", "COM2", "COM3", "COM4", "COM5" };
        string[] set_point = { "0.5", "1", "2" };//set timer
        private void Form1_Load(object sender, EventArgs e)
        {
            // Cấu hình biểu đồ ZedGraph
            GraphPane mypannel = zedGraphControl1.GraphPane;
            mypannel.Title.Text = "Biểu đồ nhiệt độ và thời gian";
            mypannel.YAxis.Title.Text = "Nhiệt độ (Độ C)";
            mypannel.XAxis.Title.Text = "Thời gian(s)";
            // Khởi tạo danh sách các điểm cho biểu đồ
            RollingPointPairList list1 = new RollingPointPairList(100000);
            // Thêm một đường biểu đồ với màu cam và ký hiệu sao
            LineItem duongline1 = mypannel.AddCurve("Nhiệt độ ", list1, Color.OrangeRed, SymbolType.Star);
            // Cài đặt giá trị trục X và Y
            mypannel.XAxis.Scale.Min = 0.0;
            mypannel.XAxis.Scale.Max = 100.0;
            mypannel.XAxis.Scale.MajorStep = 5.0;


            mypannel.YAxis.Scale.Min = 0.0;
            mypannel.YAxis.Scale.Max = 100.0;
            mypannel.YAxis.Scale.MajorStep = 5.0;
            zedGraphControl1.AxisChange();// Cập nhật thay đổi trên biểu đồ
            // Thêm các giá trị Baud rate, port name và setpoint vào ComboBox
            string[] myport = SerialPort.GetPortNames();// Lấy danh sách các cổng COM
            portName.Items.AddRange(port);
            BaudRate.Items.AddRange(baud);
            setpoint.Items.AddRange(set_point);
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        int tong = 0;// Biến đếm thời gian (được dùng làm trục X)
        public void draw(float line1)// Hàm vẽ điểm trên biểu đồ
        {
            LineItem duongline1 = zedGraphControl1.GraphPane.CurveList[0] as LineItem;
            if (duongline1 == null)
            {
                return;// Nếu đường biểu đồ không tồn tại thì thoát
            }
            IPointListEdit list1 = duongline1.Points as IPointListEdit;
            if (list1 == null)
            {
                return; // Nếu danh sách điểm không tồn tại thì thoát
            }

            list1.Add(tong, line1);// Thêm một điểm vào biểu đồ
             // Nếu số lượng điểm vượt quá 100 thì dịch biểu đồ sang phải
            if (tong > 100)
            {
                zedGraphControl1.GraphPane.XAxis.Scale.Min = tong - 100;
                zedGraphControl1.GraphPane.XAxis.Scale.Max = tong;
            }

            zedGraphControl1.AxisChange();// Cập nhật biểu đồ
            zedGraphControl1.Invalidate();// Làm mới giao diện
            tong++;// Tăng biến đếm thời gian
        }


        private void buttonConnect_click_Click(object sender, EventArgs e)// Xu ly khi nhan nut Connect
        {
            try
            {
                // Thiết lập cổng COM và Baud rate
                serCOM.PortName = portName.Text;
                serCOM.BaudRate = int.Parse(BaudRate.Text);
                serCOM.Open();// Mở kết nối cổng COM

                progressBar1.Value = 100;// Cập nhật thanh tiến trình
                buttonConnect_click.Enabled = false;// Vô hiệu hóa nút Connect
                btDisconnect.Enabled = true;// Kích hoạt nút Disconnect
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());// Hiển thị lỗi nếu không kết nối được
            }
        }

        private void btDisconnect_Click(object sender, EventArgs e) // Xử lý khi nhấn nút Disconnect
        {
            try
            {

                serCOM.Close();// Đóng kết nối cổng COM
                progressBar1.Value = 0;// Cập nhật thanh tiến trình
                buttonConnect_click.Enabled = true;// Kích hoạt nút Connect
                btDisconnect.Enabled = false;// Vô hiệu hóa nút Disconnect
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());// Hiển thị lỗi nếu không thể đóng kết nối
            }
        }

        string data = ""; // Biến lưu dữ liệu nhận từ UART
        float temperature; // Biến lưu nhiệt độ đọc được
         // Hàm xử lý khi nhận dữ liệu từ UART
        private void serCOM_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            data += serCOM.ReadLine(); // Đọc dữ liệu từ UART
            if (data.Length > 1)
            {
                // Xử lý dữ liệu: loại bỏ khoảng trắng, thay dấu phẩy bằng dấu chấm
                data = data.Trim().Replace(",", ".");
                float temperature = float.Parse(data);// Chuyển dữ liệu sang dạng số thực
                // Cập nhật giao diện trên luồng chính
                Invoke(new MethodInvoker(() =>
                {
                    textBox1.Text = data;// Hiển thị dữ liệu trong TextBox
                    draw(temperature);// Vẽ nhiệt độ trên biểu đồ
                    // Cảnh báo nhiệt độ cao
                    if (temperature > 80.00)
                    {
                        textBox1.Text = "HIGH TEMPERATURE"; // Cập nhật trực tiếp ở đây
                    }
                    else if (temperature < 50.00)
                    {
                        textBox1.Text = "";
                    }
                }));
                Invoke(new MethodInvoker(() => Box_Temp.Text = data));// Cập nhật TextBox hiển thị nhiệt độ
                data = "";// Reset dữ liệu
            }
        }



        private void portName_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
                private void button1_Click(object sender, EventArgs e) // Nút Start 
        {
            serCOM.Write("8");
            button1.BackColor= Color.Green;
        }
                private void button2_Click(object sender, EventArgs e)//Nút Stop
        {
            serCOM.Write("9");
            button2.BackColor= Color.Red;
        }
                private void zedGraphControl1_Load(object sender, EventArgs e)
        {

        }
                private void label4_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void label3_Click_1(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            serCOM.Write(setpoint.Text);//Set timer
        }
    }
}