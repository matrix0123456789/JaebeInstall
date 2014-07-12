using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {

            var Proje = new ProjektInstalatora();
            Proje.folderŹródłowy = FolSrc.Text;
            Proje.folderDocelowy = FolDoc.Text;
            Proje.nazwa = Nazwa.Text;
            Proje.wersja = Wersja.Text;
            Proje.autor = Autor.Text;
            Proje.licencja = Licencja.Text;
            Proje.zapisz();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
