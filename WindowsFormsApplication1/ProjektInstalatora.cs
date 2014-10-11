using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    enum NaglowekTypy : byte { nazwa = 1, licencja }
    enum Kompresja:byte{Brak,Zlib}
    class ProjektInstalatora
    {
        public string folderDocelowy = "";
        public string folderŹródłowy = "";
        public string nazwa;
        public string wersja;
        public string autor;
        public long dzielkompr = 1024 * 64;
        public string licencja;
        public string plikWykonywalny = "";
        public string FolderDom = "";
        public Kompresja kompresja=Kompresja.Zlib;
        public class plik
        {
            public FileInfo x;
            public string path;


            public plik(FileInfo x, string path)
            {
                // TODO: Complete member initialization
                this.x = x;
                this.path = path;
            }
        }
        List<plik> all = new List<plik>();
        public void zapisz(bool czyPrawdziwe)
        {
            for (int i = folderDocelowy.IndexOf('\\', 3); i > 0; i = folderDocelowy.IndexOf('\\', i + 1))
            {
                var dir = new DirectoryInfo(folderDocelowy.Substring(0, i));
                if (!dir.Exists)
                    dir.Create();
            }
            var dir2 = new DirectoryInfo(folderDocelowy);
            if (!dir2.Exists)
                dir2.Create();
            if (czyPrawdziwe)
                Form1.ProgressMax = liczPliki(new DirectoryInfo(folderŹródłowy));

            bin.Write((byte)kompresja.GetHashCode());
            //zapisywanie metadanych
            bin.Write(nazwa.Length * 2 + 4 + wersja.Length * 2 + 4 + autor.Length * 2 + 4 + licencja.Length * 2 + 4 + plikWykonywalny.Length * 2 + 4 + FolderDom.Length * 2 + 4);
            bin.Write(nazwa.Length * 2);
            bin.Write(nazwa.ToCharArray(), 0, nazwa.Length);
            bin.Write(wersja.Length * 2);
            bin.Write(wersja.ToCharArray(), 0, wersja.Length);
            bin.Write(autor.Length * 2);
            bin.Write(autor.ToCharArray(), 0, autor.Length);
            bin.Write(licencja.Length * 2);
            bin.Write(licencja.ToCharArray(), 0, licencja.Length);
            bin.Write(plikWykonywalny.Length * 2);
            bin.Write(plikWykonywalny.ToCharArray(), 0, plikWykonywalny.Length);
            bin.Write(FolderDom.Length * 2);
            bin.Write(FolderDom.ToCharArray(), 0, FolderDom.Length);
            if (Obrazek == "")
            {
                bin.Write(0L);
                bin.Write(0L);
            }
            else
            {
                var x = new FileInfo(Obrazek);
                var strRead = x.OpenRead();

                bin.Write((long)strRead.Length);
                var z = ZLibNet.ZLibCompressor.Compress(strRead);

                bin.Write((long)z.Length);
                for (long i = 0; i < z.Length; i++)
                {
                    bin.BaseStream.WriteByte((byte)z.ReadByte());

                }
                zapisano += 16 + (ulong)z.Length;
            }

            zapisano = (ulong)(nazwa.Length * 2 + 4 + wersja.Length * 2 + 4 + autor.Length * 2 + 4 + licencja.Length * 2 + 4 + plikWykonywalny.Length * 2 + 4 + FolderDom.Length * 2 + 4 + 4);
            if (czyPrawdziwe)
                zapiszFolder(new DirectoryInfo(folderŹródłowy), "");
            foreach(var x in all)
            {
                dodajPlik(x);
            }

            //bin.Write(0);
            bin.Close();
            // strumień.Close();
            try
            {
                System.IO.File.Copy("install.exe", folderDocelowy + "\\install.exe", true);
            }
            catch { MessageBox.Show("Nie można skopiować pliku install.exe", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error); }
            try
            {
                System.IO.File.Copy("zlib1.dll", folderDocelowy + "\\zlib1.dll", true);
            }
            catch { MessageBox.Show("Nie można skopiować pliku zlib1.dll", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error); }


        }

        private int liczPliki(DirectoryInfo folder)
        {
            var ret = folder.GetFiles().Length;
            var foldery = folder.GetDirectories();
            foreach (var x in foldery)
            {
                ret += liczPliki(x);

            }
            return ret;

        }
        void zapiszFolder(DirectoryInfo folder, string path)
        {

            var pliki = folder.GetFiles();
            foreach (var x in pliki)
            {
                if (x.FullName.Equals(folderDocelowy + "\\data1.bin", StringComparison.CurrentCultureIgnoreCase))
                {
                    Form1.Progress++;
                    continue;
                }
                var p = new plik(x, path);
                all.Add(p);
               
            }
            var foldery = folder.GetDirectories();
            foreach (var x in foldery)
            {
                zapiszFolder(x, path + x.Name + "\\");

            }
        }
        void dodajPlik(plik p)
        {
            var nazwaf = p.path + p.x.Name;
            bin.Write(nazwaf.Length * 2);
            zapisano += 4;
            //bin.Flush();
            //strumień.Write(nazwa.Length);
            bin.Write(nazwaf.ToCharArray(), 0, nazwaf.Length);
            zapisano += (ulong)nazwaf.Length * 2;

            var strRead = p.x.OpenRead();
            var plikRozm = (long)strRead.Length;
            bin.Write(plikRozm);
            zapisano += 8;
            long zTeraz = 0;

            while (zTeraz < plikRozm)
            {
                long chwil = plikRozm - zTeraz;
                if (chwil > dzielkompr)
                    chwil = dzielkompr;
                bin.Write((long)chwil);
                zapisano += 8;
                var bufOrg = new byte[chwil];
                strRead.Read(bufOrg, 0, (int)chwil);
                byte[] z;
                if (kompresja == Kompresja.Zlib) { 
                 z = ZLibNet.ZLibCompressor.Compress(bufOrg);
            }
                else 
                {
                    z = bufOrg;
                }
                bin.Write((long)z.Length);

                bin.BaseStream.Write(z, 0, z.Length);
                zapisano += (ulong)z.Length;
                zTeraz += chwil;
            }
            bin.BaseStream.Flush();
            // strumień.BaseStream.Flush();
            Form1.Progress++;
        }
        public ulong coIleDziel = long.MaxValue;
        ulong zapisano = 0;
        ulong aktData = 0;
        BinaryWriter _bin;
        BinaryWriter bin
        {
            get
            {
                if (_bin == null || zapisano / coIleDziel + 1 > aktData)
                {
                    if (_bin != null)
                        _bin.Close();
                    aktData++;
                    var strumień = new StreamWriter(folderDocelowy + "\\data" + (aktData) + ".bin");
                    _bin = new BinaryWriter(strumień.BaseStream, System.Text.Encoding.Unicode);
                }
                return _bin;
            }
        }

        public string Obrazek = "";
    }
}
