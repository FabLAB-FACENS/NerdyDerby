﻿using System.Collections;
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
    public GameObject popUp;


    // Gerador de QR Codes https://qrexplore.com/generate/
    // Gerador de Nomes https://www.nomesdefantasia.com/surnames/short/

    void Start()
    {
        takePictureButton.interactable = false;

        //Setup files folder
        if (!Directory.Exists("CarPics"))
        {
            Directory.CreateDirectory("CarPics");
        }

        //Config Arduino
        arduinoCOM = PlayerPrefs.GetString("ArduinoCOMRegistro");
        if (arduinoCOM == "")
        {
            Debug.Log("Invalid Arduino Port");
        }
        else
        {
            arduino = new SerialPort(arduinoCOM, 9600);
            arduino.ReadTimeout = 50;
            arduino.Open();
        }



        if (arduino.IsOpen)
        {
            Debug.Log("arduino OK");
        }
        else
        {
            Debug.Log("Can't open Arduino");
        }

        //Config WebCam
        string webCamIndex = PlayerPrefs.GetString("webCamIndex");
        backCam = new WebCamTexture(webCamIndex);
        if (backCam == null)
        {
            Debug.Log("Unable to find back camera");
            return;
        }
        backCam.Play();

    }

    void Update()
    {
        if (!backCam.isPlaying)
        {
            return;
        }
        background.texture = backCam;
        float ratio = (float)backCam.width / (float)backCam.height;
        fit.aspectRatio = ratio;

        float scaleY = backCam.videoVerticallyMirrored ? -1f : 1f;
        background.rectTransform.localScale = new Vector3(1f, scaleY, 1f);

        int orient = -backCam.videoRotationAngle;
        background.rectTransform.localEulerAngles = new Vector3(0, 0, orient);

        LayoutRebuilder.ForceRebuildLayoutImmediate(mainPanel);

    }

    public void TakePicture_Click()
    {
        Directory.CreateDirectory("CarPics/" + code.text);
        FileStream file = File.Open("CarPics/" + code.text + "/" + code.text + ".txt", FileMode.Create);
        BinaryWriter binary = new BinaryWriter(file);
        byte[] name = System.Text.Encoding.UTF8.GetBytes(carName.text);
        binary.Write(name);
        file.Close();

        takePictureButton.interactable = false;
        StopAllCoroutines();
        try
        {
            arduino.Write("voltah");
        }
        catch (Exception e)
        {

        }

        StartCoroutine("MakeGif");

    }

    public IEnumerator MakeGif()
    {

        for (int i = 0; i < 23; i++)
        {
            yield return new WaitForSeconds(0.5f);
            TakePicture(i);
        }
        backCam.Stop();
        if (carName.text != "")
        {
            RegisterButton.interactable = true;
        }
        //takePictureButton.interactable = true;
        StartCoroutine("ShowGif");

    }

    public IEnumerator ShowGif()
    {
        int i = 0;
        while (true)
        {
            string name = code.text + i.ToString();
            string path = code.text;
            ReadImage(path, name);
            yield return new WaitForSeconds(0.1f);
            i++;
            i = i % 23;
        }
    }

    void ReadImage(string path, string name)
    {
        AspectRatioFitter arf = background.gameObject.GetComponent<AspectRatioFitter>();
        byte[] file = File.ReadAllBytes("CarPics/" + path + "/" + name + ".png");
        Texture2D img = new Texture2D(backCam.width, backCam.height);
        img.LoadImage(file);
        background.texture = Sprite.Create(img, new Rect(0, 0, img.width, img.height), new Vector2(0.5f, 0.5f)).texture;
        float ratio = (float)backCam.width / (float)backCam.height;
        arf.aspectRatio = ratio;
    }


    public void Register_Click()
    {
        StopAllCoroutines();
        StartCoroutine(Register());

        backCam.Play();
        StartCoroutine(QRRead());
    }

    void TakePicture(int index)
    {
        //Convert to PNG
        Texture2D tex = ToTexture2D(backCam);

        FileStream file = File.Open("CarPics/" + code.text + "/" + code.text + index.ToString() + ".png", FileMode.Create);
        BinaryWriter binary = new BinaryWriter(file);
        byte[] img = tex.EncodeToPNG();
        binary.Write(img);
        file.Close();
    }

    public void Name_change()
    {

        if (carName.text != "")
        {
            takePictureButton.interactable = true;
        }
        else
        {
            takePictureButton.interactable = false;
        }
    }
    public IEnumerator Register()
    {

        if (!CodeVerify(code.text))
        {

            yield return new WaitForEndOfFrame();

            takePictureButton.interactable = false;
            carName.interactable = false;
            RegisterButton.interactable = false;
            code.text = "";
            carName.text = "";
            Resources.UnloadUnusedAssets();
            GC.Collect();
        }




    }
    public bool CodeVerify(string _code)
    {
        if (_code != "" && File.Exists("CarPics/" + _code + "/" + _code + ".txt"))
        {
            popUp.SetActive(true);
            popUp.GetComponentInChildren<Text>().text = "Código já cadastro";
            Debug.Log("Car already exisits");
            StartCoroutine(ClosePopUp());
            RegisterButton.interactable = false;
            return true;
        }
        return false;

    }

    IEnumerator ClosePopUp()
    {
        yield return new WaitForSeconds(3f);
        popUp.SetActive(false);
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

            if (result != null && Directory.Exists("CarPics/" + result.Text))
            {
                //code.text = "Carro cadastrado";
                popUp.GetComponentInChildren<Text>().text = "Carro já cadastrado";
                popUp.SetActive(true);
                StartCoroutine(ClosePopUp());
                Debug.Log("Car already exisits");
                result = null;
            }
            yield return new WaitForEndOfFrame();
        }
        code.text = result.Text;
        carName.interactable = true;
        Debug.Log("DECODED TEXT FROM QR: " + result.Text);

        //takePictureButton.interactable = true;

    }

    private void OnDisable()
    {
        //code.text = "Show QRCode in the Camera";
        carName.text = "";
        takePictureButton.interactable = false;
        RegisterButton.interactable = false;

        StopAllCoroutines();
        backCam.Stop();
        arduino.Close();
        Debug.Log("Disable");
    }

    public void ManualCodeInput()
    {
        if (code.text != "")
        {
            if (!CodeVerify(code.text))
            {
                carName.interactable = true;
                Name_change();
            }
            else
            {
                carName.interactable = false;
                takePictureButton.interactable = false;
            }

        }
        else
        {
            carName.interactable = false;
            takePictureButton.interactable = false;
        }
    }

    IEnumerator Restart()
    {
        yield return new WaitForSeconds(0.5f);
        backCam.Play();
        StartCoroutine(QRRead());

        try
        {
            arduino = new SerialPort(arduinoCOM, 9600);
            arduino.ReadTimeout = 50;
            arduino.Open();
        }
        catch (Exception e)
        {

        }




    }
    private void OnEnable()
    {
        StartCoroutine(Restart());

    }
}



