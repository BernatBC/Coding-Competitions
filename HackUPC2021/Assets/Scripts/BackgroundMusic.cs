using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BackgroundMusic : MonoBehaviour
{
    public static BackgroundMusic backgroundMusic;
    private AudioSource audioSource;
    public bool music_on = true;

    private void Start()
    {
        audioSource = FindObjectOfType<AudioSource>();
        audioSource.Play();

        if (backgroundMusic == null)
        {
            backgroundMusic = this;
            DontDestroyOnLoad(gameObject);
        }
        else
        {
            GetComponent<AudioSource>().enabled = false;
            //Destroy(gameObject);
        }
    }

    public void OnOff() {
        if (music_on) {
            music_on = false;
            audioSource.Pause();
        }
        else {
            music_on = true;
            audioSource.Play();
        }
    }
}
