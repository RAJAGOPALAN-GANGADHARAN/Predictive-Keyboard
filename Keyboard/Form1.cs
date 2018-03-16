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

namespace Keyboard
{
    public partial class Form1 : Form
    {
        string t="";
        int choice;
        StringBuilder str1 = new StringBuilder(30);
        StringBuilder str2 = new StringBuilder(30);
        StringBuilder str3 = new StringBuilder(30);
        public Form1()
        {
            InitializeComponent();
            button1.FlatAppearance.BorderColor = Color.FromArgb(0, 255, 255, 255);
            this.TopMost = true;
            //***
            

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

       
    
        [DllImport(@"C:\\Users\\Sweet Home\\Documents\\DSA\\Keyboard\\Debug\\Keyboard_schema.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void init();
        [DllImport(@"C:\\Users\\Sweet Home\\Documents\\DSA\\Keyboard\\Debug\\Keyboard_schema.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void test(string str,StringBuilder str1,StringBuilder str2,StringBuilder str3,int choice);
        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            const int margin = 10;
            //int x = Screen.PrimaryScreen.WorkingArea.Right -
               // this.Width - margin;
            int y = Screen.PrimaryScreen.WorkingArea.Bottom -
                this.Height - margin;
            
            this.Location = new Point(1980/6,y);
            init();
        }

        private void button27_Click(object sender, EventArgs e)
        {
            //test();
        }

        private void Label1_Click(object sender, EventArgs e)
        {

        }
        public void cut(string s)
        {
            s=s.ToLower();
            int index = s.IndexOf(t);
            SendKeys.Send(s.Substring(index+1));

        }
        public void single_button_Click(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            //Console.WriteLine(btn.Text);
            if (btn.Text == "space")
            {
                t = " ";
                SendKeys.Send(" ");
            }
            else
            {
                t += btn.Text;
                SendKeys.Send(btn.Text);
            }
            Console.WriteLine(t);
            test(t,str1,str2,str3,choice);
            button29.Text = str1.ToString();
            button30.Text = str2.ToString();
            button31.Text = str3.ToString();
            if (t == " ")
                t = "";

        }
        public void single_button_word_Click(object sender, EventArgs e)
        {
            Button btn = (Button)sender;
            cut(btn.Text);
            choice = Convert.ToInt32(btn.Tag);

        }


    }
}
