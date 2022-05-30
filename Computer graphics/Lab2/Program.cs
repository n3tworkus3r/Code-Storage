using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
var skCanvas = new SkiaSharp.SKCanvas(new SkiaSharp.SKBitmap());
var sKCanvasView = new SkiaSharp.Views.Forms.SKCanvasView();
sKCanvasView = skCanvas;
sKCanvasView.GestureRecognizers.ToList().ForEach(Console.WriteLine);
//SaveBMP("img.bmp", sKCanvasView);
static void SaveBMP(string filePath, SkiaSharp.Views.Forms.SKCanvasView sKCanvasView)
{
    List<(byte B, byte G, byte R)> pixelsData = new();
    File.Create(filePath);
    File.WriteAllBytes(filePath, GenerateBMP((int)sKCanvasView.Width, (int)sKCanvasView.Height, pixelsData));
    static byte[] GenerateBMP(int width, int height, List<(byte B, byte G, byte R)> pixelsData)
    {
        const int bmpHeaderSize = 14;
        const int bmpInfo = 40;
        const int datasizePerPixel = 4;
        var headerSize = bmpHeaderSize + bmpInfo;
        IEnumerable<byte> BitmapFileHeader()
        {
            var signatureFormat = BitConverter.GetBytes((short)0x4D42);
            var bitmapSize = BitConverter.GetBytes(width * height
                * datasizePerPixel + headerSize);
            var reservedNull = new byte[] { 0, 0 };
            var pixeldataStartByteOffset = BitConverter.GetBytes(headerSize);
            var bitmapFileHeader = signatureFormat
                .Concat(bitmapSize)
                .Concat(reservedNull)
                .Concat(pixeldataStartByteOffset);
            return bitmapFileHeader.Count() is bmpHeaderSize ? bitmapFileHeader
                : throw new Exception("Wrong BitmapFileHeaderSize");
        }
        IEnumerable<byte> BitmapInfo()
        {
            IEnumerable<byte> InfoFields()
            {
                var stuctSize = BitConverter.GetBytes(40);
                var byteWidth = BitConverter.GetBytes(width);
                var byteHeight = BitConverter.GetBytes(height);
                var specValue = BitConverter.GetBytes(1);
                var bitPerPixel = BitConverter.GetBytes((short)24);
                var pixelStorageType = BitConverter.GetBytes(0);
                //var hResolution = BitConverter.GetBytes();
                //var vResolution = BitConverter.GetBytes();
                var palleteSize = BitConverter.GetBytes(0);
                var palleteCellsAm = BitConverter.GetBytes(0);
                return stuctSize
                    .Concat(byteWidth)
                    .Concat(byteHeight)
                    .Concat(specValue)
                    .Concat(bitPerPixel)
                    .Concat(pixelStorageType)
                    .Concat(BitConverter.GetBytes(datasizePerPixel))
                    //.Concat(hResolution)
                    //.Concat(vResolution)
                    .Concat(palleteSize)
                    .Concat(palleteCellsAm);
            }
            byte[] bitMask = Array.Empty<byte>(),
                colorTable = Array.Empty<byte>();
            return InfoFields()
                .Concat(bitMask)
                .Concat(colorTable);
        }
        var colorProfile = Array.Empty<byte>();
        var res = BitmapFileHeader()
            .Concat(BitmapInfo())
            .Concat(colorProfile);
        foreach (var (B, G, R) in pixelsData)
            res.Concat(new byte[] { B, G, R, 0 });
        return res.ToArray();
    }
}
