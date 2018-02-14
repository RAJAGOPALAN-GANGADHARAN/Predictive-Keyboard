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
        public Form1()
        {
            InitializeComponent();
            button1.FlatAppearance.BorderColor = Color.FromArgb(0, 255, 255, 255);
            
        }
        [DllImport(@"C:\\Users\\Sweet Home\\Documents\\DSA\\Keyboard\\Debug\\Keyboard_schema.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void test();
        private void button1_Click(object sender, EventArgs e)
        {
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void button27_Click(object sender, EventArgs e)
        {
            test();
        }
    }
}
