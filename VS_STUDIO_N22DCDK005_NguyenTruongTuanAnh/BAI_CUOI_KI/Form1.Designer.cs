namespace BAI_CUOI_KI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.zedGraphControl1 = new ZedGraph.ZedGraphControl();
            this.serCOM = new System.IO.Ports.SerialPort(this.components);
            this.portName = new System.Windows.Forms.ComboBox();
            this.BaudRate = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonConnect_click = new System.Windows.Forms.Button();
            this.btDisconnect = new System.Windows.Forms.Button();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.Box_Temp = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.setpoint = new System.Windows.Forms.ComboBox();
            this.button3 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // zedGraphControl1
            // 
            this.zedGraphControl1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.zedGraphControl1.Font = new System.Drawing.Font("Times New Roman", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.zedGraphControl1.Location = new System.Drawing.Point(175, 1);
            this.zedGraphControl1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.zedGraphControl1.Name = "zedGraphControl1";
            this.zedGraphControl1.ScrollGrace = 0D;
            this.zedGraphControl1.ScrollMaxX = 0D;
            this.zedGraphControl1.ScrollMaxY = 0D;
            this.zedGraphControl1.ScrollMaxY2 = 0D;
            this.zedGraphControl1.ScrollMinX = 0D;
            this.zedGraphControl1.ScrollMinY = 0D;
            this.zedGraphControl1.ScrollMinY2 = 0D;
            this.zedGraphControl1.Size = new System.Drawing.Size(623, 451);
            this.zedGraphControl1.TabIndex = 0;
            this.zedGraphControl1.UseExtendedPrintDialog = true;
            this.zedGraphControl1.Load += new System.EventHandler(this.zedGraphControl1_Load);
            // 
            // serCOM
            // 
            this.serCOM.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serCOM_DataReceived);
            // 
            // portName
            // 
            this.portName.FormattingEnabled = true;
            this.portName.Location = new System.Drawing.Point(68, 12);
            this.portName.Name = "portName";
            this.portName.Size = new System.Drawing.Size(101, 21);
            this.portName.TabIndex = 1;
            this.portName.SelectedIndexChanged += new System.EventHandler(this.portName_SelectedIndexChanged);
            // 
            // BaudRate
            // 
            this.BaudRate.FormattingEnabled = true;
            this.BaudRate.Location = new System.Drawing.Point(68, 58);
            this.BaudRate.Name = "BaudRate";
            this.BaudRate.Size = new System.Drawing.Size(101, 21);
            this.BaudRate.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(5, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Port Name";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(4, 61);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Baud Rate";
            // 
            // buttonConnect_click
            // 
            this.buttonConnect_click.Font = new System.Drawing.Font("Times New Roman", 7.25F, System.Drawing.FontStyle.Bold);
            this.buttonConnect_click.Location = new System.Drawing.Point(8, 115);
            this.buttonConnect_click.Name = "buttonConnect_click";
            this.buttonConnect_click.Size = new System.Drawing.Size(75, 23);
            this.buttonConnect_click.TabIndex = 5;
            this.buttonConnect_click.Text = "Kết Nối";
            this.buttonConnect_click.UseVisualStyleBackColor = true;
            this.buttonConnect_click.Click += new System.EventHandler(this.buttonConnect_click_Click);
            // 
            // btDisconnect
            // 
            this.btDisconnect.Font = new System.Drawing.Font("Times New Roman", 7.25F, System.Drawing.FontStyle.Bold);
            this.btDisconnect.Location = new System.Drawing.Point(94, 115);
            this.btDisconnect.Name = "btDisconnect";
            this.btDisconnect.Size = new System.Drawing.Size(75, 23);
            this.btDisconnect.TabIndex = 6;
            this.btDisconnect.Text = "Ngắt Kết Nối";
            this.btDisconnect.UseVisualStyleBackColor = true;
            this.btDisconnect.Click += new System.EventHandler(this.btDisconnect_Click);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(11, 98);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(157, 11);
            this.progressBar1.TabIndex = 7;
            // 
            // Box_Temp
            // 
            this.Box_Temp.Location = new System.Drawing.Point(53, 196);
            this.Box_Temp.Name = "Box_Temp";
            this.Box_Temp.Size = new System.Drawing.Size(115, 20);
            this.Box_Temp.TabIndex = 10;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(5, 199);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Nhiet do";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 154);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 12;
            this.button1.Text = "START";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(93, 154);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 13;
            this.button2.Text = "STOP";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(11, 254);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(157, 20);
            this.textBox1.TabIndex = 14;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(65, 238);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(44, 13);
            this.label3.TabIndex = 15;
            this.label3.Text = "ALARM";
            this.label3.Click += new System.EventHandler(this.label3_Click_1);
            // 
            // setpoint
            // 
            this.setpoint.FormattingEnabled = true;
            this.setpoint.Location = new System.Drawing.Point(24, 304);
            this.setpoint.Name = "setpoint";
            this.setpoint.Size = new System.Drawing.Size(121, 21);
            this.setpoint.TabIndex = 16;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(44, 331);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 17;
            this.button3.Text = "SEND";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.setpoint);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.Box_Temp);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.btDisconnect);
            this.Controls.Add(this.buttonConnect_click);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.BaudRate);
            this.Controls.Add(this.portName);
            this.Controls.Add(this.zedGraphControl1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private ZedGraph.ZedGraphControl zedGraphControl1;
        private System.IO.Ports.SerialPort serCOM;
        private System.Windows.Forms.ComboBox portName;
        private System.Windows.Forms.ComboBox BaudRate;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonConnect_click;
        private System.Windows.Forms.Button btDisconnect;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.TextBox Box_Temp;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox setpoint;
        private System.Windows.Forms.Button button3;
    }
}

