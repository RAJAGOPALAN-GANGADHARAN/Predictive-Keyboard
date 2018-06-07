using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;

namespace keyboard_layout
{
    public partial class Form1 : Form
    {
        //Dll imports
        #region
        [DllImport(@"C:\\Users\\Sweet Home\\Documents\\DSA\\Keyboard\\Debug\\Keyboard_schema.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void init();
        [DllImport(@"C:\\Users\\Sweet Home\\Documents\\DSA\\Keyboard\\Debug\\Keyboard_schema.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Search(string str, StringBuilder str1, StringBuilder str2, StringBuilder str3);
        [DllImport(@"C:\\Users\\Sweet Home\\Documents\\DSA\\Keyboard\\Debug\\Keyboard_schema.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Space(string str, StringBuilder str1, StringBuilder str2, StringBuilder str3,int choice);
        [DllImport(@"C:\\Users\\Sweet Home\\Documents\\DSA\\Keyboard\\Debug\\Keyboard_schema.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Enter();
        #endregion
        //variables declaration
        #region
        StringBuilder str1 = new StringBuilder(30);
        StringBuilder str2 = new StringBuilder(30);
        StringBuilder str3 = new StringBuilder(30);
        string t="";
        int choice;
        #endregion
        //end

        public Form1()
        {
            InitializeComponent();
            this.TopMost = true;
        }
        const int WS_EX_NOACTIVATE = 0x08000000;
        protected override CreateParams CreateParams
        {
            get
            {
                CreateParams param = base.CreateParams;
                param.ExStyle |= WS_EX_NOACTIVATE;
                return param;
            }
        }
        private void button5_Click(object sender, EventArgs e)
        {

        }

        private void button26_Click(object sender, EventArgs e)
        {

        }

        private void button30_Click(object sender, EventArgs e)
        {
            button30.Font = new Font(button30.Font.FontFamily, 100);
        }

        private void button32_Click(object sender, EventArgs e)
        {

        }

        private void button31_Click(object sender, EventArgs e)
        {

        }

        private void button33_Click(object sender, EventArgs e)
        {

        }

        private void button55_Click(object sender, EventArgs e)
        {
            test_label_1.Text = " ";
            test_label_2.Text = " ";
            test_label_3.Text = " ";
            string temp = testing.Text;
            Search(temp,str1,str2,str3);
            test_label_1.Text = str1.ToString();
            test_label_2.Text = str2.ToString();
            test_label_3.Text = str3.ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            const int margin = 10;
            int y = Screen.PrimaryScreen.WorkingArea.Bottom -
                this.Height - margin;

            this.Location = new Point(1980 / 6, y);
            init();
        }
        private void send_to_screen(string f)
        {
            SendKeys.Send(f);
        }
        private void Key_press(object sender,EventArgs e)
        {
            Button btn = (Button)sender;
            t += btn.Text;
            send_to_screen(btn.Text);
            current_text.Text = t;
            Search(t, str1, str2, str3);
            set_prediction();
        }
        private void set_prediction()
        {
            predict1.Text = str1.ToString();
            str1.Length = 0;
            predict2.Text = str2.ToString();
            str2.Length = 0;
            predict3.Text = str3.ToString();
            str3.Length = 0;
        }
        private void Prediction_click(object sender,EventArgs e)
        {
            //one of prediction
            Button btn = (Button)sender;
            choice = Convert.ToInt32(btn.Tag);
            string choosen_word=btn.Text;
            test_label_1.Text = t+" "+choosen_word;
            //string code = choosen_word.Substring(choosen_word.IndexOf(t) + choosen_word.Length);
            string rest_of_string = choosen_word.ToLower().Split(new string[] { t }, StringSplitOptions.None).Last();
            test_label_2.Text = rest_of_string;
            t += rest_of_string;
            test_label_3.Text = t;
            send_to_screen(rest_of_string);
            Space_click(sender, e);
        }
        private void Space_click(object sender,EventArgs e)
        {
            //space bar click
            Space(t,str1,str2,str3,choice);
            send_to_screen(" ");
            set_prediction();
            t = "";
        }
        private void Enter_click(object sender,EventArgs e)
        {
            send_to_screen("\n");
            Enter();
        }
        private void Close(object sender,EventArgs e)
        {
            this.Close();
        }

        private void Form1_Shown(object sender, EventArgs e)
        {
            
        }
    }
}
