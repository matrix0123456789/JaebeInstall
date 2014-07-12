using System;
using System.IO;
using System.Text;

namespace WindowsFormsApplication1
{
    enum NaglowekTypy : byte { nazwa = 1, licencja }
    class ProjektInstalatora
    {
        public string folderDocelowy = "";
        public string folderŹródłowy = "";
        public string nazwa;
        public string wersja;
        public string autor;
        public string licencja;
        public string plikWykonywalny = "";
        public void zapisz()
        {
            var strumień = new StreamWriter(folderDocelowy + "\\install.bin");
            var bin = new BinaryWriter(strumień.BaseStream, System.Text.Encoding.Unicode);
            
            //zapisywanie metadanych
            bin.Write(nazwa.Length * 2 + 4 + wersja.Length * 2 + 4 + autor.Length * 2 + 4 + licencja.Length * 2 + 4);

            bin.Write(nazwa.Length * 2);
            bin.Write(nazwa.ToCharArray(),0,nazwa.Length);
            bin.Write(wersja.Length * 2);
            bin.Write(wersja.ToCharArray(), 0, wersja.Length);
            bin.Write(autor.Length * 2);
            bin.Write(autor.ToCharArray(), 0, autor.Length);
            bin.Write(licencja.Length * 2);
            bin.Write(licencja.ToCharArray(), 0, licencja.Length);
            bin.Write(plikWykonywalny.Length * 2);
            bin.Write(plikWykonywalny.ToCharArray(), 0, plikWykonywalny.Length);

            zapiszFolder(bin, new DirectoryInfo(folderŹródłowy), "");
            strumień.Close();

        }
        void zapiszFolder(BinaryWriter bin, DirectoryInfo folder, string path)
        {

            var pliki = folder.GetFiles();
            foreach (var x in pliki)
            {
                var nazwaf = path + x.Name;
                bin.Write(nazwaf.Length * 2);
                //bin.Flush();
                //strumień.Write(nazwa.Length);
                bin.Write(nazwaf.ToCharArray(), 0, nazwaf.Length);
                //strumień.Flush();
                var strRead = x.OpenRead();
                /*var buf=new byte[strRead.Length];
                strRead.Read(buf, 0, (int)strRead.Length);*/
                bin.Write(strRead.Length);
                var z = ZLibNet.ZLibCompressor.Compress(strRead);

                bin.Write(z.Length);
                //bin.Flush();
                //strumień.Write(z.Length);
                // strumień.Flush();
                for (long i = 0; i < z.Length; i++)
                    bin.BaseStream.WriteByte((byte)z.ReadByte());
                // strumień.BaseStream.Flush();
            }
            var foldery = folder.GetDirectories();
            foreach (var x in foldery)
            {
                zapiszFolder(bin, x, path + x.Name + "\\");

            }
        }
    }
}
