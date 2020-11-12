using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.IO;
using System.IO.Ports;
using System;
using UnityEngine;
using UnityEngine.UI;
using ZXing;
using ZXing.QrCode;

public class QRCodeController : MonoBehaviour
{
    SerialPort arduino;
    string arduinoCOM;
    private bool cameraAvailable;
    private WebCamTexture backCam;
    private Texture defaultBackground;
    private bool qrRoutine;
    public RawImage background;
    public AspectRatioFitter fit;
    RectTransform myRect;
    public InputField code;
    public InputField carName;
    public Button takePictureButton;
    public Button RegisterButton;
    public InputField webCamIndex;
    public RectTransform mainPanel;
    

    // Gerador de QR Codes https://qrexplore.com/generate/
    // Gerador de Nomes https://www.nomesdefantasia.com/surnames/short/

    void Start()
    {
        arduinoCOM = PlayerPrefs.GetString("ArduinoCOM");
        if (arduinoCOM == "")
        {
            Debug.Log("Invalid Arduino Port");
        }
        arduino = new SerialPort(arduinoCOM, 9600);
        arduino.ReadTimeout = 50;
        arduino.Open();

        if (arduino.IsOpen)
        {
            Debug.Log("arduino OK");
        }
        else
        {
            Debug.Log("Can't open Arduino");
        }

        string webCamIndex = PlayerPrefs.GetString("webCamIndex");
        backCam = new WebCamTexture(webCamIndex);

        if (backCam == null)
        {
            Debug.Log("Unable to find back camera");
            return;
        }
        backCam.Play();
        background.texture = backCam;
        cameraAvailable = true;
        if (!Directory.Exists("CarPics"))
        {
            Directory.CreateDirectory("CarPics");
        }
        StartCoroutine(QRRead());
        qrRoutine = true;
    }

    void Update()
    {

        if (!qrRoutine)
        {
            backCam.Play();
            StartCoroutine(QRRead());
            qrRoutine = true;
        }

        if (!cameraAvailable)
        {
            return;
        }
        float ratio = (float)backCam.width / (float)backCam.height;
        fit.aspectRatio = ratio;

        float scaleY = backCam.videoVerticallyMirrored ? -1f : 1f;
        background.rectTransform.localScale = new Vector3(1f, scaleY, 1f);

        int orient = -backCam.videoRotationAngle;
        background.rectTransform.localEulerAngles = new Vector3(0, 0, orient);

        if (code.text == "Apresente o QRCode" || backCam.isPlaying || carName.text == "")
        {
            RegisterButton.interactable = false;
        }
        else
        {
            RegisterButton.interactable = true;
        }

        LayoutRebuilder.ForceRebuildLayoutImmediate(mainPanel);
    }
    public void TakePicture_Click()
    {
        StopAllCoroutines();
        for (int i = 0; i < 24; i++)
        {
            
        }
        arduino.Write("rotate");




        backCam.Stop();
    }
    public void Register_Click()
    {
        StartCoroutine(Register());
    }
    public IEnumerator Register()
    {
        Texture2D tex = ToTexture2D(backCam);
        FileStream file = File.Open("CarPics/" + code.text + ".png", FileMode.Create);
        BinaryWriter binary = new BinaryWriter(file);
        byte[] img = tex.EncodeToPNG();
        binary.Write(img);
        file.Close();
        yield return new WaitForEndOfFrame();

        file = File.Open("CarPics/" + code.text + ".txt", FileMode.Create);
        binary = new BinaryWriter(file);
        byte[] name = System.Text.Encoding.UTF8.GetBytes(carName.text);
        binary.Write(name);
        file.Close();


        takePictureButton.interactable = false;
        code.text = "Apresente o QRCode";
        carName.text = "";
        backCam.Play();
        StartCoroutine(QRRead());

    }
    public Texture2D ToTexture2D(Texture texture)
    {

        Texture2D tex = new Texture2D(texture.width, texture.height, TextureFormat.RGB24, false);
        RenderTexture currentRT = RenderTexture.active;

        RenderTexture renderTexture = new RenderTexture(texture.width, texture.height, 32);
        Graphics.Blit(texture, renderTexture);

        RenderTexture.active = renderTexture;
        tex.ReadPixels(new Rect(0, 0, renderTexture.width, renderTexture.height), 0, 0);
        tex.Apply();
        return tex;
    }
    IEnumerator QRRead()
    {
        IBarcodeReader barcodeReader = new BarcodeReader();
        Result result = barcodeReader.Decode(backCam.GetPixels32(), backCam.width, backCam.height);
        while (result == null)
        {
            result = barcodeReader.Decode(backCam.GetPixels32(), backCam.width, backCam.height);
            //Debug.Log("Not Found");
            if (result != null && File.Exists("CarPics/" + result.Text + ".png"))
            {
                code.text = "Carro já cadastrado";
                Debug.Log("Car already exisits");
                result = null;
            }
            yield return new WaitForEndOfFrame();
        }
        code.text = result.Text;
        takePictureButton.interactable = true;
        Debug.Log("DECODED TEXT FROM QR: " + result.Text);
    }

    private void OnDisable()
    {
        code.text = "Show QRCode in the Camera";
        takePictureButton.interactable = false;
        StopAllCoroutines();
        backCam.Stop();
        Debug.Log("Disable");
        qrRoutine = false;
    }
}



