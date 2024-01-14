-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 24, 2021 at 11:54 AM
-- Server version: 10.1.38-MariaDB
-- PHP Version: 7.3.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dbhotel`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `admin_id` int(10) NOT NULL,
  `admin_name` varchar(100) NOT NULL,
  `admin_email` varchar(100) NOT NULL,
  `admin_pass` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`admin_id`, `admin_name`, `admin_email`, `admin_pass`) VALUES
(1, 'admin', 'admin@gmail.com', 'admin');

-- --------------------------------------------------------

--
-- Table structure for table `customer`
--

CREATE TABLE `customer` (
  `cust_id` int(11) NOT NULL,
  `cust_name` varchar(100) NOT NULL,
  `cust_phone` varchar(100) NOT NULL,
  `cust_address` varchar(100) NOT NULL,
  `cust_email` varchar(100) NOT NULL,
  `cust_pass` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `customer`
--

INSERT INTO `customer` (`cust_id`, `cust_name`, `cust_phone`, `cust_address`, `cust_email`, `cust_pass`) VALUES
(1, 'lisa', '0127473376', 'johor', 'lisa@gmail.com', 'Lisa_123'),
(2, 'john', '0124536788', 'kuala lumpur', 'john@gmail.com', 'John_123'),
(3, 'abu', '12345666', 'melaka', 'abu@gmail.com', 'abu123'),
(4, 'ali', '1234567899', 'selangor', 'ali@gmail.com', 'Ali_1234'),
(5, 'maria', '1234567789', 'melaka', 'maria@gmail.com', 'Maria_123');

-- --------------------------------------------------------

--
-- Table structure for table `housekeeper`
--

CREATE TABLE `housekeeper` (
  `housekeeper_id` int(10) NOT NULL,
  `housekeeper_name` varchar(100) NOT NULL,
  `housekeeper_email` varchar(100) NOT NULL,
  `housekeeper_pass` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `housekeeper`
--

INSERT INTO `housekeeper` (`housekeeper_id`, `housekeeper_name`, `housekeeper_email`, `housekeeper_pass`) VALUES
(1, 'cleaner', 'cleaner@gmail.com', 'cleaner');

-- --------------------------------------------------------

--
-- Table structure for table `reservation`
--

CREATE TABLE `reservation` (
  `reservation_id` int(11) NOT NULL,
  `reservation_date` varchar(50) NOT NULL,
  `checkin` varchar(50) NOT NULL,
  `checkout` varchar(50) NOT NULL,
  `bill` decimal(5,2) NOT NULL,
  `deposit` decimal(5,2) NOT NULL,
  `room_id` int(11) NOT NULL,
  `cust_id` int(11) NOT NULL,
  `status` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `reservation`
--

INSERT INTO `reservation` (`reservation_id`, `reservation_date`, `checkin`, `checkout`, `bill`, `deposit`, `room_id`, `cust_id`, `status`) VALUES
(1, 'Fri Jun 11 10:06:08 2021\n', '10/6/2021', '12/6/2021', '700.00', '200.00', 103, 2, 'CANCELLED'),
(2, 'Fri Jun 11 15:55:05 2021\n', '15/6/2021', '17/6/2021', '500.00', '150.00', 105, 5, 'CHECKED OUT'),
(3, 'Fri Jun 18 11:49:45 2021\n', '1/7/2021', '3/7/2021', '700.00', '150.00', 101, 2, 'CHECKED IN'),
(4, 'Fri Jun 18 12:13:17 2021\n', '1/7/2021', '3/7/2021', '400.00', '100.00', 201, 3, '');

-- --------------------------------------------------------

--
-- Table structure for table `room`
--

CREATE TABLE `room` (
  `room_id` int(11) NOT NULL,
  `room_type` varchar(255) NOT NULL,
  `room_capacity` int(11) NOT NULL,
  `room_aircond` varchar(255) NOT NULL,
  `room_tv` varchar(255) NOT NULL,
  `room_wifi` varchar(255) NOT NULL,
  `room_price` decimal(5,2) NOT NULL,
  `room_status` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `room`
--

INSERT INTO `room` (`room_id`, `room_type`, `room_capacity`, `room_aircond`, `room_tv`, `room_wifi`, `room_price`, `room_status`) VALUES
(101, 'S', 5, 'Y', 'Y', 'Y', '350.00', 'IN'),
(102, 'S', 5, 'Y', 'Y', 'Y', '350.00', 'NA'),
(103, 'S', 5, 'Y', 'Y', 'Y', '350.00', 'A'),
(104, 'S', 5, 'Y', 'Y', 'Y', '250.00', 'A'),
(105, 'S', 5, 'Y', 'Y', 'Y', '250.00', 'OUT'),
(201, 'N', 2, 'Y', 'Y', 'Y', '200.00', 'BOOKED'),
(202, 'N', 2, 'Y', 'Y', 'Y', '200.00', 'A'),
(203, 'N', 2, 'Y', 'Y', 'Y', '200.00', 'A'),
(204, 'N', 2, 'Y', 'Y', 'N', '150.00', 'A'),
(205, 'N', 2, 'Y', 'Y', 'N', '150.00', 'A');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`admin_id`);

--
-- Indexes for table `customer`
--
ALTER TABLE `customer`
  ADD PRIMARY KEY (`cust_id`);

--
-- Indexes for table `housekeeper`
--
ALTER TABLE `housekeeper`
  ADD PRIMARY KEY (`housekeeper_id`);

--
-- Indexes for table `reservation`
--
ALTER TABLE `reservation`
  ADD PRIMARY KEY (`reservation_id`),
  ADD KEY `room_id` (`room_id`),
  ADD KEY `cust_id` (`cust_id`);

--
-- Indexes for table `room`
--
ALTER TABLE `room`
  ADD PRIMARY KEY (`room_id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `admin`
--
ALTER TABLE `admin`
  MODIFY `admin_id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `customer`
--
ALTER TABLE `customer`
  MODIFY `cust_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `housekeeper`
--
ALTER TABLE `housekeeper`
  MODIFY `housekeeper_id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `reservation`
--
ALTER TABLE `reservation`
  MODIFY `reservation_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
