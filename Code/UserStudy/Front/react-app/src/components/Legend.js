import React from "react";
import Slider from "react-slick";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faAngleUp, faAngleDown } from "@fortawesome/free-solid-svg-icons";

function Line({ color }) {
  return (
    <div
      style={{
        width: "100%",
        height: "2rem",
        alignItems: "center",
        display: "flex"
      }}
    >
      <div style={{ width: "100%", height: "2px", backgroundColor: color }} />
    </div>
  );
}

function SlideItem({ text }) {
  return (
    <div
      style={{
        height: "2rem",
        alignItems: "center",
        display: "flex",
        justifyContent: "center"
      }}
    >
      {text}
    </div>
  );
}

// show/change the selected attributes for displaying the convex hull
class Legend extends React.Component {
  render() {
    const settings = {
      dots: false,
      infinite: true,
      speed: 500,
      slidesToShow: 3,
      slidesToScroll: 1,
      vertical: true,
      verticalSwiping: true,
      arrows: false,
      swipeToSlide: true,
      afterChange: this.props.changeStartingIndex
    };
    return (
      <div
        title="Click the arrows to change the selected attributes for displaying the convex hull."
        style={{
          width: "12rem"
        }}
      >
        <div
          style={{
            alignItems: "center",
            width: "4rem",
            display: "inline-block",
            verticalAlign: "middle"
          }}
        >
          <Line color="#ff0000" />
          <Line color="#00ff00" />
          <Line color="#0000ff" />
        </div>
        <div
          style={{
            width: "8rem",
            display: "inline-block",
            verticalAlign: "middle"
          }}
        >
          <div
            onClick={() => this.slider.slickPrev()}
            style={{ cursor: "pointer" }}
          >
            <FontAwesomeIcon icon={faAngleUp} />
          </div>
          <Slider {...settings} ref={self => (this.slider = self)}>
            <SlideItem text="Price (USD)" />
            <SlideItem text="Year" />
            <SlideItem text="Power (HP)" />
            <SlideItem text="Used KM" />
          </Slider>
          <div
            onClick={() => this.slider.slickNext()}
            style={{ cursor: "pointer" }}
          >
            <FontAwesomeIcon icon={faAngleDown} />
          </div>
        </div>
      </div>
    );
  }
}

export default Legend;
