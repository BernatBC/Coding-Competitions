using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
    public int points = 50;
    [SerializeField]
    private GameObject explosion;
    public GameObject explosion_sound;

    bool rectified = false;

    [SerializeField]
    private float speed = 4;
    
    [SerializeField]
    private Transform cannon;
    
    [SerializeField]
    private GameObject bullet;

    private Transform player;

    private Rigidbody2D rb2D;

    private float shootingDelay = 0.5f;
    private float nextShot = 0;
    bool targetAcquired = false;
    void Awake() {
        if (FindObjectOfType<PlayerController>() == null) return;
        player = FindObjectOfType<PlayerController>().transform;
        rb2D = GetComponent<Rigidbody2D>();
    }

    private void Update() {
        if (player != null) {
            float angle = Mathf.Atan2(player.position.y-transform.position.y, player.position.x-transform.position.x)*180 / Mathf.PI;
            if (!rectified) {
                transform.rotation = Quaternion.Slerp (transform.rotation, Quaternion.Euler (0, 0, angle), (Mathf.Clamp(Mathf.Abs(angle), 30, 150)) * 0.04f * Time.deltaTime);
            }
            Vector2 target = Vector2.zero;
            float distance = Vector2.Distance(transform.position, player.position);
            if (distance > 10) targetAcquired = false;
            if (distance > 7 && !targetAcquired) {
                target = transform.right * speed;
            }
            else targetAcquired = true;
            rb2D.velocity = Vector2.Lerp(rb2D.velocity, target, 0.025f);

            if (targetAcquired && nextShot < Time.time) {
                Instantiate(bullet, cannon.position, transform.rotation);
                nextShot = Time.time + shootingDelay;
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Bullet")
        {
            //Animation and destruction
            //Particles
            GameObject g =  Instantiate(explosion, transform.position, Quaternion.identity);
            Destroy(g, 4f);
            //Sound
            GameObject sound = Instantiate(explosion_sound);
            Destroy(sound, 2f);
            //Shake
            CinemachineShake.Instance.ShakeCamera(3f, 0.25f);
            Score_manager.score_manager.Add_score(points);
            FindObjectOfType<LevelManager>().EnemyDied();
            Destroy(gameObject);
            Destroy(collision.gameObject);
        }
    }

}
