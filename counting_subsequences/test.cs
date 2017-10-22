using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AbilityIcon : MonoBehaviour {

	public float shiftLifetime = 0.5f;
	public float width=250;
	public float yVal=-900;
	public float leftOffset=-500;

	public float fadeLifetime;

	public Image abilityImage;

	Image timerImage;

	float shiftParam = 0f;
	float fadeParam = 0f;
	float time = 0f;

	float duration = 0f;

	int index;
    int numberOfShifts;

	public bool paused = false;

	public AbilityDisplay displayer;

	// Public Functions

	public void Begin(Sprite s, int i, float t) { // This function starts everything
		SetSprite (s);
		SetIndex (i);
		Show ();
		BeginTimer (t);
	}

	public void Kill() { // turns it off 
		abilityImage.color = new Color(abilityImage.color.r, abilityImage.color.g, abilityImage.color.b, 0f);
		timerImage.color = new Color(timerImage.color.r, timerImage.color.g, timerImage.color.b, 0f);
		timerImage.fillAmount = 0f;
		index = 0;
		time = -1f;
		shiftParam = -1f;
		duration = -1f;
	}

	public void ShiftLeft(){ // Shifts an ability icon left. This is called from within abilityIcon
		if (shiftingLeft > -1) {
			index--;
			shiftParam = -1f;
			return;
		}
		++numberOfShifts;
	}

	public void AddTime(float t) {
		duration = time + t;
		time = 0f;
	}


	public int Index(){return index;}



	void Start() {
		timerImage = GetComponent <Image> ();
		abilityImage.color = new Color(abilityImage.color.r, abilityImage.color.g, abilityImage.color.b, 0f);
		timerImage.color = new Color(timerImage.color.r, timerImage.color.g, timerImage.color.b, 0f);
	}


	void Show() {
		abilityImage.color = new Color(abilityImage.color.r, abilityImage.color.g, abilityImage.color.b, 1f);
		timerImage.color = new Color(timerImage.color.r, timerImage.color.g, timerImage.color.b, 1f);
	}

	void SetIndex(int i) {
		index = i;
		// Set the position according to the index
		transform.localPosition = new Vector3(leftOffset + width*index, yVal, 0f);
	}

	void BeginTimer(float d) {
		time = 0f;
		duration = d;
	}

	void Fade(){
		fadeParam = 0f;
	}

	void SetSprite(Sprite s) {
		abilityImage.sprite = s;
	}

	void Update() {

		if (paused)
			return;
		
		if (time > -1) {
			if (time > duration*numberOfShifts) {
				Debug.Log ("counting and time > duration index is " + index.ToString ());
				displayer.Remove (this);
				Fade ();
				time = 0f;
				counting = false;
				numberOfShifts = 1;
			} else {
				timerImage.fillAmount = time / duration;
				time += Time.deltaTime;
			}
		}

		if (shiftParam > -1) {
			if (shiftParam >= 1f) {
				shiftParam = -1f;
			} else {
				// shift left;
				transform.localPosition = new Vector3(leftOffset+(1+index)*width-width*moveFunction(shiftParam), yVal, 0f);
				shiftParam += Time.deltaTime / shiftLifetime;
			}
		}
		if (fadeParam > -1) {
			if (fadeParam >= 1f) {
				fadeParam = -1f;
				abilityImage.color = new Color(abilityImage.color.r, abilityImage.color.g, abilityImage.color.b, 0f);
				timerImage.color = new Color(timerImage.color.r, timerImage.color.g, timerImage.color.b, 0f);
			} else {
				abilityImage.color = new Color(abilityImage.color.r, abilityImage.color.g, abilityImage.color.b, fadeFunction(fadeParam));
				timerImage.color = new Color(timerImage.color.r, timerImage.color.g, timerImage.color.b, fadeFunction(fadeParam));
				fadeParam += Time.deltaTime / fadeLifetime;
			}
		}
	}
		
	// An increasing function that takes 0 <= t <= 1, and returns 0 <= return <= 1
	float moveFunction(float t) {
		return t * t;
	}

	// A decreasing function that takes 0 <= t <= 1 and returns 0 <= return <= 1
	float fadeFunction(float t) {
		return 1 - t;
	}
		
}
