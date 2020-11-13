using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FadeOut : MonoBehaviour
{
    public float fadeRate = 0.0001f;
    public Image image;
    public float targetAlpha = 0f;
    public Color curColor;
    public float timeToStart;

    // Start is called before the first frame update
    void Start()
    {
        //this.targetAlpha = this.image.color.a;
        //this.targetAlpha = 0f;

        StartCoroutine(myFadeOut());
    }

    // Update is called once per frame
    void Update()
    {

    }

    private IEnumerator myFadeOut()
    {
        image.color = Color.white;
        curColor = image.color;
        float alphaDiff = Mathf.Abs(curColor.a - this.targetAlpha);
        yield return new WaitForSeconds(timeToStart);

        while (alphaDiff > 0.01f)
        {
            curColor.a = curColor.a - fadeRate;
            this.image.color = curColor;
            alphaDiff = Mathf.Abs(curColor.a - this.targetAlpha);
            Debug.Log(alphaDiff);
            yield return new WaitForSeconds(fadeRate);
        }
        curColor.a = 0;
        this.image.color = curColor;
        yield return new WaitForSeconds(1f);
       
    }
}
