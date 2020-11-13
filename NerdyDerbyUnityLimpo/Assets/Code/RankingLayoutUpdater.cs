using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class RankingLayoutUpdater : MonoBehaviour
{
    VerticalLayoutGroup hlg;
    // Start is called before the first frame update
    void Start()
    {
        hlg = gameObject.GetComponent<VerticalLayoutGroup>();
    }

    // Update is called once per frame
    void Update()
    {
        
        Canvas.ForceUpdateCanvases();
        hlg.CalculateLayoutInputHorizontal();
        hlg.CalculateLayoutInputVertical();
        hlg.SetLayoutHorizontal();
        hlg.SetLayoutVertical();
    }
}
